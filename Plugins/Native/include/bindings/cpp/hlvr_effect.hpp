#pragma once

#include "detail/hlvr_native_handle_owner.hpp"
#include "hlvr_error.hpp"
#include "HLVR.h"
#include <cassert>

namespace hlvr {
namespace detail {

	using effect_traits = native_traits<HLVR_Effect, decltype(&HLVR_Effect_Create), decltype(&HLVR_Effect_Destroy)>;
}

class effect : public detail::native_handle_owner<effect, detail::effect_traits> {
public:
	using effect_handle = detail::native_handle_owner<effect, detail::effect_traits>;

	effect() : effect_handle{ &HLVR_Effect_Destroy } {}

	status_code play() {
		assert(m_handle);
		return status_code(HLVR_Effect_Play(m_handle.get()));
	}

	status_code pause() {
		assert(m_handle);
		return status_code(HLVR_Effect_Pause(m_handle.get()));
	}

	status_code reset() {
		assert(m_handle);
		return status_code(HLVR_Effect_Reset(m_handle.get()));
	}

	expected<HLVR_EffectInfo, status_code> get_info() {
		assert(m_handle);
		HLVR_EffectInfo info = { 0 };
		auto ec = HLVR_Effect_GetInfo(m_handle.get(), &info);
		if (HLVR_OK(ec)) {
			return info;
		}
		else {
			return make_unexpected(status_code(ec));
		}
	}

	static expected<effect, status_code> make() {
		return make_helper(&HLVR_Effect_Create);
	}

private:
	friend effect_handle;
	explicit effect(HLVR_Effect* rawPtr) : effect_handle( rawPtr, &HLVR_Effect_Destroy ) {}

};
}