/*! \file HLVR_Experimental.h
	\brief Experimental and unstable features
	\copyright Copyright 2017 NullSpace VR, Inc All Rights reserved.
*/
#ifndef __HLVR_INCLUDE_HLVR_EXPERIMENTAL_H__
#define __HLVR_INCLUDE_HLVR_EXPERIMENTAL_H__


#include <stdint.h>
#include "HLVR_Forwards.h"
#include "HLVR_Errors.h"


#ifdef HLVR_EXPORTS
#define HLVR_EXPERIMENTAL_API __declspec(dllexport) 
#else
#define HLVR_EXPERIMENTAL_API __declspec(dllimport) 
#endif

#define HLVR_RETURN_EXP(ReturnType) HLVR_EXPERIMENTAL_API ReturnType __cdecl

#ifdef __cplusplus
extern "C" {
#endif

	/* Note: 
	*	
	*	Functions and data structures in this header file are subject to breaking changes within minor API upgrades.
	*/


	typedef struct HLVR_BodyView HLVR_BodyView;


	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_Create(HLVR_BodyView** body);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_Release(HLVR_BodyView** body);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_Poll(HLVR_BodyView* body, HLVR_System* system);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetNodeCount(HLVR_BodyView* body, uint32_t* outNodeCount);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetNodeType(HLVR_BodyView * body, uint32_t nodeIndex, uint32_t* outType);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetNodeRegion(HLVR_BodyView * body, uint32_t nodeIndex, uint32_t* outRegion);

	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetIntensity(HLVR_BodyView * body, uint32_t nodeIndex, float* outIntensity);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_BodyView_GetWaveform(HLVR_BodyView* body, uint32_t nodeIndex, int32_t* outWaveform);
	
	typedef struct HLVR_Quaternion {
		float w;
		float x;
		float y;
		float z;
	} HLVR_Quaternion;

	typedef struct HLVR_Vector3f {
		float x;
		float y;
		float z;
	} HLVR_Vector3f;

	typedef struct HLVR_TrackingUpdate {
		HLVR_Quaternion chest;
		HLVR_Quaternion left_upper_arm;
		HLVR_Quaternion left_forearm;
		HLVR_Quaternion right_upper_arm;
		HLVR_Quaternion right_forearm;

		HLVR_Vector3f chest_gravity;
		HLVR_Vector3f chest_compass;

		HLVR_Vector3f left_upper_arm_gravity;
		HLVR_Vector3f left_upper_arm_compass;

		HLVR_Vector3f left_forearm_gravity;
		HLVR_Vector3f left_forearm_compass;

		HLVR_Vector3f right_upper_arm_gravity;
		HLVR_Vector3f right_upper_arm_compass;

		HLVR_Vector3f right_forearm_gravity;
		HLVR_Vector3f right_forearm_compass;
	} HLVR_TrackingUpdate;

	

	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_Tracking_GetOrientation(HLVR_System* ptr, uint32_t region, HLVR_Quaternion* outOrientation);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_Tracking_GetCompass(HLVR_System* ptr, uint32_t region, HLVR_Vector3f* outCompass);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_Tracking_GetGravity(HLVR_System* ptr, uint32_t region, HLVR_Vector3f* outGravity);
	
	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_Tracking_Enable(HLVR_System* ptr, uint32_t device_id);
	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_Tracking_Disable(HLVR_System* ptr, uint32_t device_id);


	HLVR_RETURN_EXP(HLVR_Result) HLVR_System_PushEvent(HLVR_System* system, const HLVR_Event* data);

	

#ifdef __cplusplus
}
#endif

#endif // __HLVR_INCLUDE_HLVR_EXPERIMENTAL_H_