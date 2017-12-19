/*! \file HLVR.h
	\brief C Interface for the Hardlight VR haptic interaction library.
	\copyright Copyright 2017 NullSpace VR, Inc All Rights reserved.
*/

#ifndef __HLVR_INCLUDE_HLVR_H__
#define __HLVR_INCLUDE_HLVR_H__



#include "HLVR_Errors.h"

#include <stdint.h>

#ifdef HLVR_EXPORTS
#define HLVR_API __declspec(dllexport) 
#else
#define HLVR_API __declspec(dllimport) 
#endif

#define HLVR_API_VERSION_MAJOR 1
#define HLVR_API_VERSION_MINOR 0
#define HLVR_API_VERSION_PATCH 0
#define HLVR_API_VERSION ((HLVR_API_VERSION_MAJOR << 24) | (HLVR_API_VERSION_MINOR << 16) | HLVR_API_VERSION_PATCH)

#if !defined(HLVR_TOSTRING)
	#define	HLVR_TOSTRINGH(x) #x
	#define HLVR_TOSTRING(x) HLVR_TOSTRINGH(x)
#endif

#if !defined(HLVR_VERSION_STRING)
	#define HLVR_VERSION_STRING HLVR_TOSTRING(HLVR_API_VERSION_MAJOR.HLVR_API_VERSION_MINOR.HLVR_API_VERSION_PATCH)
#endif


#define HLVR_RETURN(ReturnType) HLVR_API ReturnType __cdecl



#ifdef __cplusplus
extern "C" {
#endif


	

	/*! Special value indicating that an HLVR_NodeIterator should iterate over all nodes in the system.
		@see HLVR_NodeIterator_Next
	*/
	const uint32_t hlvr_allnodes = 0;

	
	
	/*! Reserves space between regions */
	#define HLVR_SUBREGION_BLOCK 1000000
	
	/*!
		A set of one or more HLVR_Regions are used to specify where particular events should take place. 
	*/

	const uint32_t hlvr_region_UNKNOWN = 0;
	const uint32_t hlvr_region_body = 1 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_torso = 2 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_torso_front = 3 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_middle_sternum =  3 * HLVR_SUBREGION_BLOCK + 1;
	const uint32_t hlvr_region_chest_left = 4 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_chest_right = 5 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_ab_left = 6 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_middle_ab_left = 7 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_lower_ab_left = 8 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_ab_right = 9 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_middle_ab_right = 10 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_lower_ab_right = 11 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_torso_back = 12 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_torso_left = 13 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_torso_right = 14 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_back_left = 15 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_back_right = 16 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_arm_left = 17 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_lower_arm_left = 18 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_arm_right = 19 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_lower_arm_right = 20 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_shoulder_left = 21 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_shoulder_right = 22 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_leg_left = 23 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_lower_leg_left = 24 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_upper_leg_right = 25 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_lower_leg_right = 26 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_head = 27 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_palm_left = 28 * HLVR_SUBREGION_BLOCK;
	const uint32_t hlvr_region_palm_right = 29 * HLVR_SUBREGION_BLOCK;

	
	/*!
		Opaque type representing the main context object used in the HLVR API. 

		@note Unless otherwise noted, calls into the Hardlight API using an HLVR_System object are only valid while that object is alive and has not been destroyed. 
	*/
	typedef struct HLVR_System HLVR_System;

	/*! 
		Opaque type used as a data source in the creation of effects to be played on Hardlight-compatible hardware.

		Many different event types can be represented using HLVR_Event, by setting key-value pairs and asking the API to interpret the data as a certain type of
		event. 

		@see HLVR_Timeline_AddEvent
	*/
	typedef struct HLVR_Event HLVR_Event;

	/*! 
		Opaque type representing a time-ordered data container which groups together one or more events.
	*/
	typedef struct HLVR_Timeline HLVR_Timeline;

	/*!
		Opaque type representing a playable effect active in the system, such as a haptic traversal of the body. 

		An HLVR_Effect is essentially a handle which can be manipulated to start, stop, reset, and retrieve info about an effect within the system. 
	*/
	typedef struct HLVR_Effect HLVR_Effect;

	
	typedef struct HLVR_Event HLVR_Event;
	/*!
		General description of a device connected to the system.
	*/
	typedef enum HLVR_DeviceConcept {
		HLVR_DeviceConcept_UNKNOWN,
		HLVR_DeviceConcept_Suit,
		HLVR_DeviceConcept_Controller,
		HLVR_DeviceConcept_Headwear,
		HLVR_DeviceConcept_Gun,
		HLVR_DeviceConcept_Sword,
		HLVR_DeviceConcept_Gauntlet,
		HLVR_DeviceConcept_MIN = HLVR_INT32_MIN,
		HLVR_DeviceConcept_MAX = HLVR_INT32_MAX
	} HLVR_DeviceConcept;

	/*
		Observed connection status of a device recognized by the system.

		@note If a device was previously connected and is now disconnected physically, the device will still be
		enumerated with a Disconnected status
		
		@see HLVR_DeviceIterator_Init
		@see HLVR_DeviceIterator_Next
	*/
	typedef enum HLVR_DeviceStatus {
		HLVR_DeviceStatus_UNKNOWN = 0,
		HLVR_DeviceStatus_Connected = 1,
		HLVR_DeviceStatus_Disconnected = 2,
		HLVR_DeviceStatus_MIN = HLVR_INT32_MIN,
		HLVR_DeviceStatus_MAX = HLVR_INT32_MAX
	} HLVR_DeviceStatus;

	/*!
		High-level information about a device recognized by the system.
	*/
	typedef struct HLVR_DeviceInfo {
		/*! Unique ID; not necessarily persisted through service restarts */
		uint32_t Id;
		/*! Friendly name  */
		char Name[128];
		/*! General concept */
		HLVR_DeviceConcept Concept;
		/*! Connection status to the host */
		HLVR_DeviceStatus Status;
	} HLVR_DeviceInfo;

	/*!
		General description of a particular node connected to the system.

		A node can be a haptic motor, kicker, LED, IMU, etc. Nodes can be commanded on a per-device basis, or as a complete system. 
		In normal usage of the API, effects are targeted to certain regions on the body which are then forwarded to the correct nodes. If necessary nodes can be
		directly targeted.

		@see HLVR_Region
		@see HLVR_Event
	*/
	typedef enum HLVR_NodeConcept {
		HLVR_NodeConcept_UNKNOWN = 0,
		HLVR_NodeConcept_Haptic,
		HLVR_NodeConcept_LED,
		HLVR_NodeConcept_InertialTracker,
		HLVR_NodeConcept_AbsoluteTracker,
		HLVR_NodeConcept_MIN = HLVR_INT32_MIN,
		HLVR_NodeConcept_MAX = HLVR_INT32_MAX
	} HLVR_NodeConcept;

	/*!
		High-level information about a node recognized by the system
	*/
	typedef struct HLVR_NodeInfo {
		/*! Unique ID; not necessarily persisted through service restarts */
		uint32_t Id;
		/*! Friendly name */
		char Name[128];
		/*! General concept */
		HLVR_NodeConcept Concept;
	} HLVR_NodeInfo;


	/*!
		Fundamental waveforms which may be combined to form more complex units of haptic feedback. 

		@see HLVR_Event
	*/
	typedef enum HLVR_Waveform {
		HLVR_Waveform_UNKNOWN = 0,
		HLVR_Waveform_Bump = 1,
		HLVR_Waveform_Buzz = 2,
		HLVR_Waveform_Click = 3,
		HLVR_Waveform_Fuzz = 5,
		HLVR_Waveform_Hum = 6,
		HLVR_Waveform_Pulse = 8,
		HLVR_Waveform_Tick = 11,
		HLVR_Waveform_Double_Click = 4,
		HLVR_Waveform_Triple_Click = 16,
		HLVR_Waveform_MIN = HLVR_INT32_MIN,
		HLVR_Waveform_MAX = HLVR_INT32_MAX
	} HLVR_Waveform;

	


	/*!
		Specify which type of type of event should be created when adding to an HLVR_Timeline

		@see HLVR_Timeline_AddEvent
	*/
	typedef enum HLVR_EventType {
		HLVR_EventType_UNKNOWN = 0,
		HLVR_EventType_DiscreteHaptic = 1,
		HLVR_EventType_BufferedHaptic = 3,
		HLVR_EventType_BeginAnalogAudio = 4,
		HLVR_EventType_EndAnalogAudio = 5,
		HLVR_EventType_MIN = HLVR_INT32_MIN,
		HLVR_EventType_MAX = HLVR_INT32_MAX
	} HLVR_EventType;

	
	/*! Properties that can be set on an HLVR_Event.

	When a key has a common prefix, such as Where_Regions and Where_Nodes for SimpleHaptic, it means that only one of keys
	should be specified. For example, a SimpleHaptic can target a particular set of device nodes, or a particular set of regions, but not both.
	*/
	typedef enum HLVR_EventKey {
		HLVR_EventKey_UNKNOWN = 0,
		/* Common Keys */
		HLVR_EventKey_Target_Regions_UInt32s,
		HLVR_EventKey_Target_Nodes_UInt32s,

		/* Event-Specific keys */
		HLVR_EventKey_DiscreteHaptic_Repetitions_UInt32 = 1000,
		HLVR_EventKey_DiscreteHaptic_Strength_Float,
		HLVR_EventKey_DiscreteHaptic_Waveform_Int,


		HLVR_EventKey_BufferedHaptic_Samples_Floats = 3000,
		HLVR_EventKey_BufferedHaptic_Frequency_Float,

		HLVR_EventKey_BeginAnalogAudio_Reserved = 4000,
		HLVR_EventKey_EndAnalogAudio_Reserved = 5000,

		HLVR_EventKey_MIN = HLVR_INT32_MIN,
		HLVR_EventKey_MAX = HLVR_INT32_MAX

	} HLVR_EventKey;


	/*! 
		Used to enumerate all devices recognized by the system at a point in time.

		When iterating over devices, the current device's info will be stored in the DeviceInfo member. 

		Reusing the same iterator object for a new enumeration after a previous one will yield devices that are observed at that moment in time, and not necessarily ones that were 
		observed in a previous enumeration.

		@note The struct must be initialized with HLVR_DeviceIterator_Init.
		@note This struct can be declared on the stack. 

		@see HLVR_DeviceIterator_Init
		@see HLVR_DeviceIterator_Next
	*/
	typedef struct HLVR_DeviceIterator {
		void* _internal;
		HLVR_DeviceInfo DeviceInfo;
	} HLVR_DeviceIterator;


	/*! 
		Used to enumerate all nodes registered to a particular device recognized by the system.

		When iterating over nodes, the current node's info will be stored in the NodeInfo member.

		Reusing the same iterator object for a new enumeration after a previous one will yield nodes that are observed at that moment in time, and not necessarily ones that were 
		observed in a previous enumeration.

		@note The struct must be initialized with HLVR_NodeIterator_Init.
		@note This struct has no associated Destroy call and can be declared on the stack.

		@see HLVR_NodeIterator_Init
		@see HLVR_NodeIterator_Next
	*/
	typedef struct HLVR_NodeIterator {
		void* _internal;
		HLVR_NodeInfo NodeInfo;
	} HLVR_NodeIterator;

	

	/*!	
		The playback state of an existing HLVR_Effect.

		When first instantiated in the system by way of HLVR_Timeline_Transmit, an HLVR_Effect will be in the Idle state.
	*/
	typedef enum HLVR_EffectInfo_State {
		HLVR_EffectInfo_State_UNKNOWN = 0,
		HLVR_EffectInfo_State_Playing,
		HLVR_EffectInfo_State_Paused,
		HLVR_EffectInfo_State_Idle,
		HLVR_EffectInfo_State_MIN = HLVR_INT32_MIN,
		HLVR_EffectInfo_State_MAX = HLVR_INT32_MAX
	} HLVR_EffectInfo_State;

	/*!	
		Stores basic information about an effect including total duration, playback state, and elapsed time.

		To check if an effect has completed playback, test if Elapsed >= Duration. 
	*/
	typedef struct HLVR_EffectInfo {
		/*! Approximate duration in fractional seconds */
		float Duration;
		/*! Approximate elapsed progress in fractional seconds */
		float Elapsed;
		/*! Playback state*/
		HLVR_EffectInfo_State PlaybackState;
	} HLVR_EffectInfo;


	/*! Information about the runtime service that the system is connected to.
		@see HLVR_System_GetRuntimeInfo
	*/
	typedef struct HLVR_RuntimeInfo {
		int32_t MajorVersion;
		int32_t MinorVersion;
		int32_t PatchVersion;
	} HLVR_RuntimeInfo;

	/*! Unused configuration object for the system.
	*/
	typedef struct HLVR_SystemConfiguration HLVR_SystemConfiguration;

	/*! 
		Unless otherwise noted, all calls into the API:
		- will return HLVR_Error_NullArgument if a required argument is nullptr
		- will return HLVR_Error_Unspecified if an unknown error occurs
		- should not be assumed thread-safe
	*/

	
	/*! Create a new Hardlight API context, establishing communicating between this application and the Hardlight runtime service.  
		
		Usage:
			@code
			HLVR_System* system = nullptr;
			if (HLVR_FAIL(HLVR_System_Create(&system, nullptr))) {
				//oh no, we couldn't instantiate the system!
			}
			@endcode

		@param system address of the target system pointer
		@param config currently ignored, may pass nullptr
		@return HLVR_Ok if the context was created successfully
		
	*/
	HLVR_RETURN(HLVR_Result) HLVR_System_Create(HLVR_System** system);

	/*! Destroy the context, shutting down communication between this application and the Hardlight runtime service.
		@param system address of the target system pointer
		@return void
	*/
	HLVR_RETURN(void) HLVR_System_Destroy(HLVR_System* system);

	/*! Checks if this version of the API has a particular feature.
		@param feature name of feature
		@return 1 if has feature, else 0
	*/
	HLVR_RETURN(int) HLVR_Version_HasFeature(const char* feature);

	/*! Retrieves version of this API in the format (major << 24) | (minor << 16) | patch
		@return uint32_t representing version of the API
	*/
	HLVR_RETURN(uint32_t) HLVR_Version_Get(void);
	
	HLVR_RETURN(const char*) HLVR_Version_GetString(void);

	/*! Checks if this header file is compatible with the supplied library.
		@return 1 if compatible, else 0
	*/
	static int HLVR_Version_IsCompatibleDLL(void)
	{
		unsigned int major = HLVR_Version_Get() >> 24;
		return major == HLVR_API_VERSION_MAJOR;
	}

	/*! Retrieves information about the current connection to the runtime service.
		@param system current context
		@param[out] info struct to be populated
		@return HLVR_Ok if able to retrieve information, HLVR_Error_ServiceIncompatible if incompatible service version, HLVR_Error_ServiceNotConnected if not connected to Service.
	*/
	HLVR_RETURN(HLVR_Result) HLVR_System_GetRuntimeInfo(const HLVR_System* system, HLVR_RuntimeInfo* info);


	/*! Suspend execution of the effects engine.
	
		Useful within a game pause routine.

		@param system current context
		@return HLVR_Ok on success
		@see HLVR_System_ResumeEffects
	*/
	HLVR_RETURN(HLVR_Result) HLVR_System_SuspendEffects(HLVR_System* system);

	/*! Resume execution of the effects engine.
		
		Useful within a game resume routine.
		Only effects that were paused due to a call to HLVR_System_SuspendEffects() will be resumed

		@param system current context
		@return HLVR_Ok on success
		@see HLVR_System_SuspendEffects
	*/
	HLVR_RETURN(HLVR_Result) HLVR_System_ResumeEffects(HLVR_System* system);

	/*! Cancel all effects, invalidating all HLVR_Effect handles. 

		Useful within a game quit routine or a level change where only new HLVR_Effects will be used

		@param system current context
		@return HLVR_Ok on success
	*/
	HLVR_RETURN(HLVR_Result) HLVR_System_CancelEffects(HLVR_System* system);


	/*! Initialize an HLVR_DeviceIterator.

		@note Must be called before using HLVR_DeviceIterator_Next() 
	*/
	HLVR_RETURN(HLVR_Result) HLVR_DeviceIterator_Init(HLVR_DeviceIterator* iter);

	/*! Advance the iterator to the next device in the system.

		Usage: 
			@code
			HLVR_System* system; //created elsewhere
			HLVR_DeviceIterator deviceIt;
			HLVR_DeviceIterator_Init(&deviceIt);
			while (HLVR_OK(HLVR_DeviceIterator_Next(&deviceIt, system))) {
				std::cout << deviceIt.DeviceInfo.Id << '\n';
			}
			@endcode
		@param iter target iterator
		@param system current context
		@return HLVR_Ok if a device was retrieved, HLVR_Error_NoMoreDevices if the iterator is finished.
	*/
	HLVR_RETURN(HLVR_Result) HLVR_DeviceIterator_Next(HLVR_DeviceIterator* iter, HLVR_System* system);


	/*! Initialize an HLVR_NodeIterator.
		@param iter target iterator
	*/
	HLVR_RETURN(HLVR_Result) HLVR_NodeIterator_Init(HLVR_NodeIterator* iter);

	/*! Advance the iterator to the next node in the system

		Usage for enumerating all nodes on a specific device:
			@code
			HLVR_System* system; //created elsewhere
			uint32_t my_device = 13; //retrieved elsewhere
			HLVR_NodeIterator nodeIt;
			HLVR_NodeIterator_Init(&nodeIt);
			while (HLVR_OK(HLVR_NodeIterator_Next(&nodeIt, my_device, system))) {
				std::cout << nodeIt.NodeInfo.Id << '\n';
			}
			@endcode

		Usage for enumerating all nodes, per device:
			@code
			HLVR_System* system; //created elsewhere
			HLVR_DeviceIterator deviceIt;
			HLVR_DeviceIterator_Init(&deviceIt);
			while (HLVR_OK(HLVR_DeviceIterator_Next(&deviceIt, system))) {
				HLVR_NodeIterator nodeIt;
				HLVR_NodeIterator_Init(&nodeIt);
				std::cout << "Device " << deviceIt.DeviceInfo.Id << " contains: \n";
				while (HLVR_OK(HLVR_NodeIterator_Next(&nodeIt, deviceIt.DeviceInfo.Id, system))) {
					std::cout << "Node " << nodeIt.NodeInfo.Id << '\n';
				}
			}
			@endcode

		Usage for enumerating all nodes:
			@code
			HLVR_System* system; //created elsewhere
			HLVR_NodeIterator nodeIt;
			HLVR_NodeIterator_Init(&nodeIt);
			while (HLVR_OK(HLVR_NodeIterator_Next(&nodeIt, hlvr_allnodes, system))) {
				std::cout << nodeIt.NodeInfo.Id << '\n';
			}
			@endcode

		@param iter target iterator
		@param device_id the device from which to retrieve retrieve nodes. If special ID hlvr_allnodes is supplied,
		all nodes in the system will be enumerated.
		@param system current context
		@return 
			- HLVR_Ok if a node was retrieved
			- HLVR_Error_NoMoreNodes if the iterator is finished.
			- HLVR_Error_NoMoreNodes if an unknown @p device_id is supplied
	*/
	HLVR_RETURN(HLVR_Result) HLVR_NodeIterator_Next(HLVR_NodeIterator* iter, uint32_t device_id, HLVR_System* system);

	
	
	/*! Create a new HLVR_Event object with a given type

		To check if an event is valid, call HLVR_Event_Validate()
		@param event address of the target event pointer which will be written to on success
		@param type type of the event
		@return HLVR_Ok on success
	*/

	HLVR_RETURN(HLVR_Result) HLVR_Event_Create(HLVR_Event** event, HLVR_EventType type);
	/*! Destroy an HLVR_Event object
		@param event address of the target event pointer to destroy
		@return void
	*/
	HLVR_RETURN(void)		 HLVR_Event_Destroy(HLVR_Event* event);

	/*! Set a float with the given key 
		@param event target
		@param key key
		@param value value
		@return HLVR_Ok 
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetFloat(HLVR_Event* event, HLVR_EventKey key, float value);
	/*! Set an array of floats with the given key
		@param event target
		@param key key
		@param values value array
		@param length length of @p values
		@return HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetFloats(HLVR_Event* event, HLVR_EventKey key, const float* values, unsigned int length);
	/*! Set an int with the given key
		@param event target
		@param key key
		@param value value
		@return HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetInt(HLVR_Event* event, HLVR_EventKey key, int value);
	/*! Set an array of ints with the given key
		@param event target
		@param key key
		@param values value array
		@param length length of @p values
		@return HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetInts(HLVR_Event* event, HLVR_EventKey key, const int* values, unsigned int length);
	/*! Set an unsigned 32-bit int with the given key
		@param event target
		@param key key
		@param value value
		@return HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetUInt32(HLVR_Event* event, HLVR_EventKey key, uint32_t value);
	/*! Set an unsigned 32-bit int array with the given key
		@param event target
		@param key key
		@param values value array
		@param length length of @p values
		@return HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetUInt32s(HLVR_Event * event, HLVR_EventKey key, const uint32_t* values, unsigned int length);
	/*! Set an unsigned 64-bit int with the given key
		@param event target
		@param key key
		@param value value
		@return HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetUInt64(HLVR_Event * event, HLVR_EventKey key, uint64_t value);
	/*! Set an unsigned 64-bit int array with the given key
		@param event target
		@param key key
		@param values value array
		@param length length of @p values
		@return HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_SetUInt64s(HLVR_Event * event, HLVR_EventKey key, const uint64_t* values, unsigned int length);








	/*! 
		The error value associated with the parse result of a given key
	*/
	typedef enum HLVR_Event_KeyParseError {
		HLVR_Event_KeyParseError_UNKNOWN,
		HLVR_Event_KeyParseError_KeyRequired,
		HLVR_Event_KeyParseError_InvalidValue,		/*!< the value did not satisfy constraints of the event, e.g. only non-negative numbers */
		HLVR_Event_KeyParseError_WrongValueType,	/*!< the value exists for the given key, yet it is of the wrong type */
		HLVR_Event_KeyParseError_MIN = HLVR_INT32_MIN,
		HLVR_Event_KeyParseError_MAX = HLVR_INT32_MAX
	} HLVR_Event_KeyParseError;


	/*! Parse error for a particular key */
	typedef struct HLVR_Event_KeyParseResult {
		HLVR_EventKey Key;
		HLVR_Event_KeyParseError Error;
	} HLVR_Event_KeyParseResult;

	/*! Set of validation errors generated by the system when parsing an event.
		@see HLVR_Event_Validate
		@see HLVR_Event
	*/
	typedef struct HLVR_Event_ValidationResult {
		/*! How many errors */
		int Count;
		/*! Value of the errors */
		HLVR_Event_KeyParseResult Errors[32];
	} HLVR_Event_ValidationResult;

	/*! Validate @p event against the parser for the given event @p type.

		Useful as a debugging tool when writing wrappers for other languages.

		@param event the event to validate
		@param outResult where to put validation results 
		@return HLVR_Error_InvalidEventType if the given type is unknown, else HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Event_Validate(const HLVR_Event* event, HLVR_Event_ValidationResult* outResult);

	
	/*! Create a new timeline
		@return HLVR_Ok on success
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Timeline_Create(HLVR_Timeline** timeline);
	
	/*! Destroy the given timeline
		@return void
	*/
	HLVR_RETURN(void)		 HLVR_Timeline_Destroy(HLVR_Timeline* timeline);
	
	/*! Add an event with a given type and time offset to this timeline
		@param timeline the timeline to operate on
		@param timeOffsetSeconds the time offset of the event, in fractional seconds (e.g. 3.4f)
		@param event the data to use when adding the event
		@return HLVR_Error_InvalidTimeOffset if @p timeOffsetSeconds < 0, else HLVR_Ok
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Timeline_AddEvent(HLVR_Timeline* timeline, double timeOffsetSeconds, const HLVR_Event* event);
	
	/*! Create a new effect within the system, using a timeline as the source
		@param timeline the source timeline
		@param system current context
		@param effect target HLVR_Effect 
		@return HLVR_Error_EmptyTimeline if timeline contains no events, else HLVR_Ok 
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Timeline_Transmit(const HLVR_Timeline* timeline, HLVR_System* system, HLVR_Effect* effect);

	/*! Create a new HLVR_Effect
		@return HLVR_Ok on success
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Effect_Create(HLVR_Effect** handlePtr);
	/*! Destroy the given HLVR_Effect
		The effect will still play out until completion.
		@return HLVR_Ok on success
	*/
	HLVR_RETURN(void)		 HLVR_Effect_Destroy(HLVR_Effect* handlePtr);
	/*! Cause the effect to play, or resume playback from a paused state.
		@return HLVR_Ok on success, HLVR_Error_NoSuchEffect if the effect was destroyed or not yet bound
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Effect_Play(HLVR_Effect* handle);
	/*! Cause the effect to pause.
		@return HLVR_Ok on success, HLVR_Error_NoSuchEffect if the effect was destroyed or not yet bound
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Effect_Pause(HLVR_Effect* handle);
	/*! Cause the effect to scrub back to beginning, placing the effect into the idle state.
		@return HLVR_Ok on success, HLVR_Error_NoSuchEffect if the effect was destroyed or not yet bound
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Effect_Reset(HLVR_Effect* handle);
	/*! Return information associated with this effect.
		@return HLVR_Ok on success, else HLVR_Error_NoSuchEffect if the effect was destroyed or not yet bound
	*/
	HLVR_RETURN(HLVR_Result) HLVR_Effect_GetInfo(const HLVR_Effect* effect, HLVR_EffectInfo* info);


	HLVR_RETURN(const char*) HLVR_ErrorString(HLVR_Result result);



#ifdef __cplusplus
}
#endif


#endif //__HLVR_INCLUDE_HLVR_H__