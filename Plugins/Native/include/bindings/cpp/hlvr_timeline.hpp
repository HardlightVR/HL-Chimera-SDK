#pragma once


#include "detail/hlvr_native_handle_owner.hpp"

#include "hlvr_event.hpp"
#include "hlvr_system.hpp"
#include "hlvr_effect.hpp"
#include "hlvr_error.hpp"

#include "HLVR.h"
#include <cassert>

namespace hlvr {

namespace detail {
	using timeline_traits = native_traits<HLVR_Timeline, decltype(&HLVR_Timeline_Create), decltype(&HLVR_Timeline_Destroy)>;
}

class timeline : public detail::native_handle_owner<timeline, detail::timeline_traits> {
public:
	using timeline_handle = detail::native_handle_owner<timeline, detail::timeline_traits>;
	timeline() : timeline_handle { &HLVR_Timeline_Destroy } {}


	

	status_code add_event(const hlvr::event& ev, double timeOffsetFractionalSeconds) {
		assert(m_handle);
		return status_code(HLVR_Timeline_AddEvent(m_handle.get(), timeOffsetFractionalSeconds, ev.native_handle()));
	}

	status_code transmit(hlvr::system& system, hlvr::effect& effect) const {
		assert(m_handle);
		assert(system);
		assert(effect);

		auto sc = HLVR_Timeline_Transmit(m_handle.get(), system.native_handle(), effect.native_handle());
		return status_code(sc);
	}

	expected<hlvr::effect, status_code> transmit(hlvr::system& system) const {
		assert(m_handle);
		assert(system);

	
		auto potentialEffect = hlvr::effect::make();
		if (!potentialEffect) {
			return potentialEffect;
		}

		hlvr::status_code sc = transmit(system, *potentialEffect);
		if (sc) { 
			return potentialEffect;
		}
		else {
			return unexpected<status_code>(sc);
		}
		
		

	}

	static expected<timeline, status_code> make() {
		return make_helper(&HLVR_Timeline_Create);
	}

private:
	friend timeline_handle;
	timeline(HLVR_Timeline* rawPtr) : timeline_handle(rawPtr, &HLVR_Timeline_Destroy) {}

};

}