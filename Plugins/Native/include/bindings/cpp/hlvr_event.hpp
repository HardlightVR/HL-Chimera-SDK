#pragma once

#include "detail/hlvr_native_handle_owner.hpp"
#include "hlvr_error.hpp"
#include "HLVR.h"
#include <cassert>

namespace hlvr {
namespace detail {

struct event_create {
	event_create(HLVR_EventType type) : m_type{ type } {}
	HLVR_Result operator()(HLVR_Event** event) {
		return HLVR_Event_Create(event, m_type);
	}
	HLVR_EventType m_type;

};
	using event_traits = native_traits<HLVR_Event, event_create, decltype(&HLVR_Event_Destroy)>;

}

class event : public detail::native_handle_owner<event, detail::event_traits> {
public:
	// detail::event_create(type), 

	using event_handle = detail::native_handle_owner<event, detail::event_traits>;
	event() : event_handle{ &HLVR_Event_Destroy } {}



	status_code set_float(HLVR_EventKey key, float val) {
		assert(m_handle);
		return status_code(HLVR_Event_SetFloat(m_handle.get(), key, val));
	}

	status_code set_floats(HLVR_EventKey key, const float* values, uint32_t length) {
		assert(m_handle);
		return status_code(HLVR_Event_SetFloats(m_handle.get(), key, values, length));
	}

	status_code set_uint32(HLVR_EventKey key, uint32_t val) {
		assert(m_handle);
		return status_code(HLVR_Event_SetUInt32(m_handle.get(), key, val));
	}
	status_code set_uint32s(HLVR_EventKey key, const uint32_t* values, uint32_t length) {
		assert(m_handle);
		assert(values);
		return status_code(HLVR_Event_SetUInt32s(m_handle.get(), key, values, length));
	}

	status_code set_int(HLVR_EventKey key, int val) {
		assert(m_handle);
		return status_code(HLVR_Event_SetInt(m_handle.get(), key, val));
	}

	static expected<event, status_code> make(HLVR_EventType type) {
		return make_helper(detail::event_create(type));
	}
private:
	friend event_handle;
	explicit event(HLVR_Event* rawPtr) : event_handle(rawPtr, &HLVR_Event_Destroy) {}

};


inline expected<HLVR_Event_ValidationResult, status_code> validate_event(const event& ev) {
	HLVR_Event_ValidationResult result;
	auto sc = HLVR_Event_Validate(ev.native_handle(), &result);
	if (HLVR_OK(sc)) {
		return result;
	}
	else {
		return make_unexpected(status_code(sc));
	}
}


}