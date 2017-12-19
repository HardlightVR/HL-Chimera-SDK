/*! \file HLVR_Forwards.h
	\brief Forward declarations for the Hardlight API
	\copyright Copyright 2017 NullSpace VR, Inc All Rights reserved.
*/

#ifndef __HLVR_INCLUDE_HLVR_FORWARDS_H__
#define __HLVR_INCLUDE_HLVR_FORWARDS_H__

typedef struct HLVR_System HLVR_System;
typedef struct HLVR_Timeline HLVR_Timeline;
typedef struct HLVR_Effect HLVR_Effect;
typedef struct HLVR_Event HLVR_Event;

typedef struct HLVR_Quaternion HLVR_Quaternion;
typedef struct HLVR_TrackingUpdate HLVR_TrackingUpdate;

typedef struct HLVR_DeviceIterator HLVR_DeviceIterator;
typedef struct HLVR_DeviceInfo  HLVR_DeviceInfo;
typedef enum HLVR_DeviceConcept HLVR_DeviceConcept;
typedef enum HLVR_DeviceStatus HLVR_DeviceStatus;

typedef struct HLVR_NodeIterator HLVR_NodeIterator;
typedef struct HLVR_NodeInfo HLVR_NodeInfo;
typedef enum HLVR_NodeConcept HLVR_NodeConcept;

typedef struct HLVR_RuntimeInfo HLVR_RuntimeInfo;

typedef struct HLVR_EffectInfo HLVR_EffectInfo;
typedef enum HLVR_EffectInfo_State HLVR_EffectInfo_State;

typedef enum HLVR_EventKey HLVR_EventKey;
typedef enum HLVR_EventType HLVR_EventType;

typedef enum HLVR_Region HLVR_Region;
typedef enum HLVR_Waveform HLVR_Waveform;

typedef enum HLVR_SuccessTypes HLVR_SuccessTypes;
typedef enum HLVR_ErrorTypes HLVR_ErrorTypes;

#endif //__HLVR_INCLUDE_HLVR_FORWARDS_H__