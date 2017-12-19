/*! \file HLVR_Errors.h
	\brief Error handling for the Hardlight API
	\copyright Copyright 2017 NullSpace VR, Inc All Rights reserved.
*/

#ifndef __HLVR_INCLUDE_HLVR_ERRORS_H__
#define __HLVR_INCLUDE_HLVR_ERRORS_H__


#include <stdint.h>



typedef int32_t HLVR_Result;

#define HLVR_INT32_MIN 0x80000000
#define HLVR_INT32_MAX 0x7FFFFFFF
static const int32_t hlvr_int32max = 0x7FFFFFFF;
static const int32_t hlvr_int32min = 0x80000000;

/*!
	Check if an HLVR_Result indicates success.
	Checking if the result evaluates to true is not sufficient; if you need to know that a call succeeded you must
	call HLVR_OK
*/
#ifndef HLVR_OK
#define HLVR_OK(result) (result >= 0)
#endif

/*! 
	Check if an HLVR_Result indicates failure.
	Checking if the result evaluates to false is not sufficient; if you need to know that a call failed you must call
	HLVR_FAIL
*/
#ifndef HLVR_FAIL
#define HLVR_FAIL(result) (!HLVR_OK(result))
#endif


/*!
	Different types of success codes that an API call may return.
*/
typedef enum HLVR_SuccessTypes {
	HLVR_Ok = 0,
	
	HLVR_Ok_MIN = HLVR_INT32_MIN,
	HLVR_Ok_MAX = HLVR_INT32_MAX

	
} HLVR_SuccessTypes;


/*!
	Different types of failure codes that an API call may return.
*/
typedef enum HLVR_ErrorTypes {

	HLVR_Error_UNKNOWN				= 0,
	/* General errors */
	HLVR_Error_Unspecified			= -1000, /*!< Catch-all error*/
	HLVR_Error_NullArgument			= -1001, /*!< Argument was nullptr */
	HLVR_Error_InvalidArgument		= -1002, /*!< Argument does not satisfy a precondition */
	HLVR_Error_BadAlloc				= -1003, /*!< Failed to allocate memory */

	/* Event errors */
	HLVR_Error_InvalidEventType		= -2000, /*!< Event type is not recognized by the system */

	/* Service errors */
	HLVR_Error_ServiceNotConnected	= -4000, /*!< Not connected to the Hardlight runtime service */
	HLVR_Error_ServiceIncompatible  = -4001, /*!< The runtime is an incompatible version */
	/* Effect errors */
	HLVR_Error_NoSuchEffect			= -5000, /*!< The HLVR_Effect was already released and cannot be used anymore */
	HLVR_Error_UninitializedEffect	= -5001, /*!< The HLVR_Effect was never initialized with a timeline */

	/* Iterator errors */
	HLVR_Error_NoMoreDevices		= -6000, /*!< There are no more devices to enumerate */
	HLVR_Error_NoMoreNodes			= -7000, /*!< There are no more nodes to enumerate, or the device specified in HLVR_NodeIterator_Next does not exist */

	/* Timeline errors */
	HLVR_Error_InvalidTimeOffset	= -8000, /*!< The time argument was < 0.0 */
	HLVR_Error_EmptyTimeline		= -8001, /*!< The HLVR_Timeline that was transmitted had no events */

	/* Tracking */
	HLVR_Error_TrackedRegionNotFound= -9001,

	HLVR_Error_MIN = HLVR_INT32_MIN,
	HLVR_Error_MAX = HLVR_INT32_MAX


} HLVR_ErrorTypes;

#endif //__HLVR_INCLUDE_HLVR_ERRORS_H__
