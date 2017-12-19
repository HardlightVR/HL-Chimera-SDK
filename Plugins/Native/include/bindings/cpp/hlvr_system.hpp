#pragma once

#include <vector>
#include "HLVR.h"
#include "HLVR_Experimental.h"
#include "detail/hlvr_native_handle_owner.hpp"
#include "hlvr_event.hpp"
#include "hlvr_error.hpp"

#include <cassert>

namespace hlvr {

namespace detail {

	using system_traits = native_traits<HLVR_System, decltype(&HLVR_System_Create), decltype(&HLVR_System_Destroy)>;

}

namespace version {

	struct version_info {
		int major;
		int minor;
		int patch;
	};


	static bool is_compatible_headers() {
		return static_cast<bool>(HLVR_Version_IsCompatibleDLL());
	}

	static const char* get_string() {
		return HLVR_Version_GetString();
	}

	static version_info get() {
		uint32_t v = HLVR_Version_Get();

		uint32_t major_mask = 0xFF000000;
		uint32_t minor_mask = 0x00FF0000;
		uint32_t patch_mask = 0x0000FFFF;

		version_info info;
		info.major = (v & major_mask) >> 24;
		info.minor = (v & minor_mask) >> 16;
		info.patch = (v & patch_mask);
		return info;
	}

   static bool is_at_least(int major, int minor, int patch) {
		version_info info = get();

		if (info.major < major) return false;
		if (info.major > major) return true;
		if (info.minor < minor) return false;
		if (info.minor > minor) return true;
		if (info.patch < patch) return false;
		return true;
	}

	

}

struct nodes_t {};
struct regions_t {};

const static nodes_t nodes{};
const static regions_t regions{};



class system : public detail::native_handle_owner<system, detail::system_traits> {
public:
	using system_handle = detail::native_handle_owner<system, detail::system_traits>;
	using region_t = uint32_t;
	using node_t = uint32_t;
	using device_t = uint32_t;

	system() : system_handle(&HLVR_System_Destroy) {}
	void shutdown() {
		m_handle.reset(nullptr);
	}

	expected<HLVR_RuntimeInfo, status_code> get_runtime_info() const {
		assert(m_handle);
		HLVR_RuntimeInfo info = { 0 };
		auto ec = HLVR_System_GetRuntimeInfo(m_handle.get(), &info);
		if (HLVR_OK(ec)) {
			return info;
		}
		else {
			return make_unexpected(status_code(ec));
		}
	}

	std::vector<HLVR_DeviceInfo> get_known_devices() {
		assert(m_handle);

		std::vector<HLVR_DeviceInfo> devices;

		HLVR_DeviceIterator iter;
		HLVR_DeviceIterator_Init(&iter);

		while (HLVR_OK(HLVR_DeviceIterator_Next(&iter, m_handle.get()))) {
			devices.push_back(iter.DeviceInfo);
		}

		return devices;
	}

	std::vector<HLVR_NodeInfo> get_nodes(device_t device_id) {
		assert(m_handle);

		std::vector<HLVR_NodeInfo> nodes;

		HLVR_NodeIterator iter;
		HLVR_NodeIterator_Init(&iter);

		while (HLVR_OK(HLVR_NodeIterator_Next(&iter, device_id, m_handle.get()))) {
			nodes.push_back(iter.NodeInfo);
		}

		return nodes;
	}

	expected<HLVR_Quaternion, status_code> get_orientation(region_t region) {
		assert(m_handle);
		HLVR_Quaternion quat = { 0 };
		auto sc = HLVR_System_Tracking_GetOrientation(m_handle.get(), region, &quat);
		if (HLVR_OK(sc)) {
			return quat;
		}
		return make_unexpected(status_code(sc));
	}

	std::vector<HLVR_NodeInfo> get_all_nodes() {
		return get_nodes(hlvr_allnodes);
	}

	
	status_code push_event(hlvr::event& event) {
		assert(m_handle);
		assert(event);
		return status_code(HLVR_System_PushEvent(m_handle.get(), event.native_handle()));
	}


	

	status_code enable_tracking(device_t device_id) {
		assert(m_handle);
		return status_code(HLVR_System_Tracking_Enable(m_handle.get(), device_id));
	}

	status_code disable_tracking(device_t device_id) {
		assert(m_handle);
		return status_code(HLVR_System_Tracking_Disable(m_handle.get(), device_id));
	}

	
	static expected<system, status_code> make() {
		return make_helper(&HLVR_System_Create);
	}

	status_code suspend_all_haptics() {
		assert(m_handle);
		return status_code( HLVR_System_SuspendEffects(m_handle.get()));
	}

	status_code resume_all_haptics() {
		assert(m_handle);
		return status_code(HLVR_System_ResumeEffects(m_handle.get()));
	}

	status_code cancel_all_haptics() {
		assert(m_handle);
		return status_code(HLVR_System_CancelEffects(m_handle.get()));
	}

private:
	friend class system_handle;
	explicit system(HLVR_System* handle) : system_handle( handle, &HLVR_System_Destroy ) {}
};


}