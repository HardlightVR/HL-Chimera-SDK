#pragma once

#include "HLVR.h"
#include <memory>
#include <cassert>
#include "../hlvr_error.hpp"

namespace hlvr {


	template <class E> class unexpected {
	public:
		static_assert(!std::is_same<E, void>::value, "E must not be void");

		unexpected() = delete;
		constexpr explicit unexpected(const E &e) : m_val(e) {}

		constexpr explicit unexpected(E &&e) : m_val(std::move(e)) {}

		/// \returns the contained value
		/// \group unexpected_value
		constexpr const E &value() const & { return m_val; }
		/// \group unexpected_value
		constexpr E &value() & { return m_val; }
		/// \group unexpected_value
		constexpr E &&value() && { return std::move(m_val); }
		/// \exclude
		constexpr const E &&value() const && { return std::move(m_val); }

	private:
		E m_val;
	};


	template<typename TResult, typename TOther>
	class expected {
	public:
		expected(TResult res) : value(std::move(res)), err(TOther()), is_expected(true) {}
		expected(unexpected<TOther> err) : err(std::move(err)), is_expected(false) {}

		constexpr const TResult *operator->() const { return valptr(); }
		constexpr TResult *operator->() { return valptr(); }

		explicit operator bool() const noexcept {
			return is_expected;
		}

		constexpr const TResult &operator*() const & { return value; }
		constexpr TResult &operator*() & { return value; }
		constexpr const TResult &&operator*() const && { return std::move(value); }
		constexpr TResult &&operator*() && { return std::move(value); }


		constexpr const TOther &error() const & { return err.value(); }
		constexpr TOther &error() & { return err.value(); }
		constexpr const TOther &&error() const && { return std::move(err.value()); }
		constexpr TOther &&error() && { return std::move(err.value()); }
	private:
		TResult *valptr() { return std::addressof(this->value); }

		TResult value;
		unexpected<TOther> err;
		bool is_expected;
	};




	template <class E> unexpected<E> make_unexpected(E &&e) {
		return unexpected<E>(std::forward<E>(e));
	}



	namespace detail {
		template<typename NativeHandle, typename Creator, typename Deleter>
		struct native_traits {
			using native_handle_type = NativeHandle;
			using creator_type = Creator;
			using deleter_type = Deleter;
		};
	

		template<typename T, class Traits>
		class native_handle_owner {
	
		public:


			typename  const Traits::native_handle_type* native_handle() const noexcept {
				return m_handle.get();
			}

			typename Traits::native_handle_type* native_handle() noexcept {
				return m_handle.get();
			}

			explicit operator bool() const noexcept {
				return (bool)m_handle;
			}
			native_handle_owner(typename Traits::deleter_type d) : m_handle{nullptr, d} {}

			

		protected:
			static expected<T, status_code> make_helper(typename Traits::creator_type c) {
				Traits::native_handle_type* handle = nullptr;
				HLVR_Result sc = c(&handle);
				if (HLVR_OK(sc)) {
					return T(handle);
				}
				else {
					return make_unexpected(status_code(sc));
				}
			}
			explicit native_handle_owner(typename Traits::native_handle_type* raw_ptr, typename Traits::deleter_type del) : m_handle{ nullptr, del } {
				m_handle.reset(raw_ptr);
			}

			std::unique_ptr<typename Traits::native_handle_type, typename Traits::deleter_type> m_handle;


		};

	}
}