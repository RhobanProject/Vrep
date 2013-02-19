// This file is part of the REMOTE API
// 
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// The REMOTE API is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The REMOTE API is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// The REMOTE API is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the REMOTE API.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

#ifndef _EXTAPI__
#define _EXTAPI__

#ifdef NON_MATLAB_PARSING /* when compiling, make sure NON_MATLAB_PARSING is always defined! */
	#include "extApiPlatform.h"
	#include "v_repConst.h"
#else 
	typedef char simxChar;
	typedef short simxShort;
	typedef unsigned short simxUShort;	
	typedef int simxInt;
	typedef unsigned int simxUInt;
	typedef float simxFloat;
	typedef void simxVoid;
	typedef double simxDouble;
#endif /* else NON_MATLAB_PARSING */

#ifdef _WIN32
	#define EXTAPI_DLLEXPORT extern __declspec(dllexport)
#endif
#if defined (__linux) || defined (__APPLE__)
	#define EXTAPI_DLLEXPORT extern
#endif

/* Use following to test endianness detection on little endian machines (endianness of the client is handled on the server side)
#define ENDIAN_TEST
*/

#ifdef NON_MATLAB_PARSING

#define SIMX_INIT_BUFF_SIZE 500
#define SIMX_MIN_BUFF_INCR 500

#define _REPLY_WAIT_TIMEOUT_IN_MS 5000
#define _MIN_COMMUNICATION_DELAY_IN_MS 5
#define _MIN_SPLIT_AMOUNT_IN_BYTES 100

/* Various other functions, not to be called directly */
simxVoid _waitUntilMessageArrived(simxInt* error);
simxChar* _setLastFetchedCmd(simxChar* cmdPtr,simxInt* error);

simxChar* _exec_null(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt* error);
simxChar* _exec_int(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxInt* error);
simxChar* _exec_intint(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue1,simxInt intValue2,simxInt* error);
simxChar* _exec_string(simxInt cmdRaw,simxInt opMode,simxChar options,const simxChar* stringValue,simxInt* error);
simxChar* _exec_int_int(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxInt intValue2,simxInt* error);
simxChar* _exec_intint_int(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue1,simxInt intValue2,simxInt intValue3,simxInt* error);
simxChar* _exec_intint_buffer(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue1,simxInt intValue2,simxChar* buffer,simxInt bufferSize,simxInt* error);
simxChar* _exec_int_float(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxFloat floatValue,simxInt* error);
simxChar* _exec_int_buffer(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxChar* buffer,simxInt bufferSize,simxInt* error);
simxChar* _exec_string_buffer(simxInt cmdRaw,simxInt opMode,simxChar options,const simxChar* stringValue,simxChar* buffer,simxInt bufferSize,simxInt* error);

simxChar _readPureDataChar(simxChar* commandPointer,simxInt stringCnt,simxInt byteOffset);
simxInt _readPureDataInt(simxChar* commandPointer,simxInt stringCnt,simxInt byteOffset);
simxFloat _readPureDataFloat(simxChar* commandPointer,simxInt stringCnt,simxInt byteOffset);
simxInt _getCmdDataSize(simxChar* commandPointer);

simxChar* _getCommandPointer_(simxInt cmdRaw,const simxChar* commandBufferStart,simxInt commandBufferSize);
simxChar* _getCommandPointer_i(simxInt cmdRaw,simxInt intValue,const simxChar* commandBufferStart,simxInt commandBufferSize);
simxChar* _getCommandPointer_ii(simxInt cmdRaw,simxInt intValue1,simxInt intValue2,const simxChar* commandBufferStart,simxInt commandBufferSize);
simxChar* _getCommandPointer_s(simxInt cmdRaw,const simxChar* stringValue,const simxChar* commandBufferStart,simxInt commandBufferSize);

simxChar* _appendCommand_(simxInt cmd,simxChar options,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxChar* _appendCommand_i(simxInt cmd,simxChar options,simxInt intValue,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxChar* _appendCommand_ii(simxInt cmd,simxChar options,simxInt intValue1,simxInt intValue2,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxChar* _appendCommand_s(simxInt cmd,simxChar options,const simxChar* stringValue,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxChar* _appendCommand_i_i(simxInt cmd,simxChar options,simxInt intValue,simxInt intValue2,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxChar* _appendCommand_ii_i(simxInt cmd,simxChar options,simxInt intValue1,simxInt intValue2,simxInt intValue3,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxChar* _appendCommand_i_f(simxInt cmd,simxChar options,simxInt intValue,simxFloat floatValue,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxChar* _appendCommand_i_buff(simxInt cmd,simxChar options,simxInt intValue,simxChar* buffer,simxInt bufferSize,simxUShort delayOrSplit,simxChar* destBuffer,simxInt* destBuffer_bufferSize,simxInt* destBuffer_dataSize);
simxChar* _appendCommand_ii_buff(simxInt cmd,simxChar options,simxInt intValue1,simxInt intValue2,simxChar* buffer,simxInt bufferSize,simxUShort delayOrSplit,simxChar* destBuffer,simxInt* destBuffer_bufferSize,simxInt* destBuffer_dataSize);
simxChar* _appendCommand_s_buff(simxInt cmd,simxChar options,const simxChar* stringValue,simxChar* buffer,simxInt bufferSize,simxUShort delayOrSplit,simxChar* destBuffer,simxInt* destBuffer_bufferSize,simxInt* destBuffer_dataSize);

simxChar* _appendChunkToBuffer(const simxChar* chunk,simxInt chunkSize,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize);
simxVoid _removeChunkFromBuffer(const simxChar* bufferStart,simxChar* chunkStart,simxInt chunkSize,simxInt* buffer_dataSize);

simxInt _removeCommandReply_null(simxInt cmdRaw);
simxInt _removeCommandReply_int(simxInt cmdRaw,simxInt intValue);
simxInt _removeCommandReply_intint(simxInt cmdRaw,simxInt intValue1,simxInt intValue2);
simxInt _removeCommandReply_string(simxInt cmdRaw,const char* stringValue);

simxChar* _getSameCommandPointer(const simxChar* cmdPtr,simxChar* cmdBuffer,simxInt cmdBufferSize);
SIMX_THREAD_RET_TYPE _communicationThread(simxVoid* p);

simxUShort _getCRC(const simxChar* data,simxInt length);

simxChar _sendMessage_socket(const simxChar* message,simxInt messageSize);
simxChar* _receiveReplyMessage_socket(simxInt* messageSize);
simxChar _sendSimplePacket_socket(const simxChar* packet,simxShort packetLength,simxShort packetsLeft);
simxInt _receiveSimplePacket_socket(simxChar* packet,simxShort* packetSize);

#endif /* NON_MATLAB_PARSING */


/* The remote API functions */
EXTAPI_DLLEXPORT simxInt simxGetJointPosition(simxInt jointHandle,simxFloat* position,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetJointPosition(simxInt jointHandle,simxFloat position,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetJointMatrix(simxInt jointHandle,simxFloat* matrix,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetSphericalJointMatrix(simxInt jointHandle,simxFloat* matrix,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetJointTargetVelocity(simxInt jointHandle,simxFloat targetVelocity,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetJointTargetPosition(simxInt jointHandle,simxFloat targetPosition,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxJointGetForce(simxInt jointHandle,simxFloat* force,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetJointForce(simxInt jointHandle,simxFloat force,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxReadForceSensor(simxInt forceSensorHandle,simxChar* state,simxFloat* forceVector,simxFloat* torqueVector,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxBreakForceSensor(simxInt forceSensorHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxReadVisionSensor(simxInt sensorHandle,simxChar* detectionState,simxFloat** auxValues,simxInt** auxValuesCount,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectHandle(const simxChar* objectName,simxInt* handle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetVisionSensorImage(simxInt sensorHandle,simxInt* resolution,simxChar** image,simxChar options,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetVisionSensorImage(simxInt sensorHandle,simxChar* image,simxInt bufferSize,simxChar options,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetVisionSensorDepthBuffer(simxInt sensorHandle,simxInt* resolution,simxFloat** buffer,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectChild(simxInt parentObjectHandle,simxInt childIndex,simxInt* childObjectHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectParent(simxInt childObjectHandle,simxInt* parentObjectHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxReadProximitySensor(simxInt sensorHandle,simxChar* detectionState,simxFloat* detectedPoint,simxInt* detectedObjectHandle,simxFloat* detectedSurfaceNormalVector,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxLoadModel(const simxChar* modelPathAndName,simxChar options,simxInt* baseHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxLoadUI(const simxChar* uiPathAndName,simxChar options,simxInt* count,simxInt** uiHandles,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxLoadScene(const simxChar* scenePathAndName,simxChar options,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxStartSimulation(simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxPauseSimulation(simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxStopSimulation(simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetUIHandle(const simxChar* uiName,simxInt* handle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetUISlider(simxInt uiHandle,simxInt uiButtonID,simxInt* position,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetUISlider(simxInt uiHandle,simxInt uiButtonID,simxInt position,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetUIEventButton(simxInt uiHandle,simxInt* uiEventButtonID,simxInt* auxValues,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetUIButtonProperty(simxInt uiHandle,simxInt uiButtonID,simxInt* prop,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetUIButtonProperty(simxInt uiHandle,simxInt uiButtonID,simxInt prop,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxAddStatusbarMessage(const simxChar* message,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsoleOpen(const simxChar* title,simxInt maxLines,simxInt mode,simxInt* position,simxInt* size,simxFloat* textColor,simxFloat* backgroundColor,simxInt* consoleHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsoleClose(simxInt consoleHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsolePrint(simxInt consoleHandle,const simxChar* txt,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsoleShow(simxInt consoleHandle,simxChar showState,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectOrientation(simxInt objectHandle,simxInt relativeToObjectHandle,simxFloat* eulerAngles,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectPosition(simxInt objectHandle,simxInt relativeToObjectHandle,simxFloat* position,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetObjectOrientation(simxInt objectHandle,simxInt relativeToObjectHandle,const simxFloat* eulerAngles,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetObjectPosition(simxInt objectHandle,simxInt relativeToObjectHandle,const simxFloat* position,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetObjectParent(simxInt objectHandle,simxInt parentObject,simxChar keepInPlace,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetUIButtonLabel(simxInt uiHandle,simxInt uiButtonID,const simxChar* upStateLabel,const simxChar* downStateLabel,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetLastErrors(simxInt* errorCnt,simxChar** errorStrings,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetArrayParameter(simxInt paramIdentifier,simxFloat* paramValues,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetArrayParameter(simxInt paramIdentifier,const simxFloat* paramValues,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetBooleanParameter(simxInt paramIdentifier,simxChar* paramValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetBooleanParameter(simxInt paramIdentifier,simxChar paramValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetIntegerParameter(simxInt paramIdentifier,simxInt* paramValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetIntegerParameter(simxInt paramIdentifier,simxInt paramValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetFloatingParameter(simxInt paramIdentifier,simxFloat* paramValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetFloatingParameter(simxInt paramIdentifier,simxFloat paramValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetStringParameter(simxInt paramIdentifier,simxChar** paramValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetCollisionHandle(const simxChar* collisionObjectName,simxInt* handle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetDistanceHandle(const simxChar* distanceObjectName,simxInt* handle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxReadCollision(simxInt collisionObjectHandle,simxChar* collisionState,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxReadDistance(simxInt distanceObjectHandle,simxFloat* minimumDistance,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxRemoveObject(simxInt objectHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxRemoveUI(simxInt uiHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxCloseScene(simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjects(simxInt objectType,simxInt* objectCount,simxInt** objectHandles,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxDisplayDialog(const simxChar* titleText,const simxChar* mainText,simxInt dialogType,const simxChar* initialText,simxFloat* titleColors,simxFloat* dialogColors,simxInt* dialogHandle,simxInt* uiHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxEndDialog(simxInt dialogHandle,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetDialogInput(simxInt dialogHandle,simxChar** inputText,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetDialogResult(simxInt dialogHandle,simxInt* result,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxCopyPasteObjects(const simxInt* objectHandles,simxInt objectCount,simxInt** newObjectHandles,simxInt* newObjectCount,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectSelection(simxInt** objectHandles,simxInt* objectCount,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetObjectSelection(const simxInt* objectHandles,simxInt objectCount,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxClearFloatSignal(const simxChar* signalName,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxClearIntegerSignal(const simxChar* signalName,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxClearStringSignal(const simxChar* signalName,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetFloatSignal(const simxChar* signalName,simxFloat* signalValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetIntegerSignal(const simxChar* signalName,simxInt* signalValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetStringSignal(const simxChar* signalName,simxChar** signalValue,simxInt* signalLength,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetFloatSignal(const simxChar* signalName,simxFloat signalValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetIntegerSignal(const simxChar* signalName,simxInt signalValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetStringSignal(const simxChar* signalName,const simxChar* signalValue,simxInt signalLength,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectFloatParameter(simxInt objectHandle,simxInt parameterID,simxFloat* parameterValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetObjectFloatParameter(simxInt objectHandle,simxInt parameterID,simxFloat parameterValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetObjectIntParameter(simxInt objectHandle,simxInt parameterID,simxInt* parameterValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetObjectIntParameter(simxInt objectHandle,simxInt parameterID,simxInt parameterValue,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxGetModelProperty(simxInt objectHandle,simxInt* prop,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxSetModelProperty(simxInt objectHandle,simxInt prop,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxRMLPosition(simxInt dofs,simxDouble timeStep,simxInt flags,const simxDouble* currentPosVelAccel,const simxDouble* maxVelAccelJerk,const simxChar* selection,const simxDouble* targetPosVel,simxInt* rmlState,simxDouble* newPosVelAccel,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxRMLVelocity(simxInt dofs,simxDouble timeStep,simxInt flags,const simxDouble* currentPosVelAccel,const simxDouble* maxAccelJerk,const simxChar* selection,const simxDouble* targetVel,simxInt* rmlState,simxDouble* newPosVelAccel,simxInt operationMode);

/* Very first function to call */
EXTAPI_DLLEXPORT simxInt simxStart(const simxChar* connectionAddress,simxInt connectionPort,simxChar waitUntilConnected,simxChar doNotReconnectOnceDisconnected,simxInt timeOutInMs);

/* Very last function to call */
EXTAPI_DLLEXPORT simxVoid simxFinish();

/* The remote API helper functions */
EXTAPI_DLLEXPORT simxInt simxGetPingTime(simxInt* pingTime);
EXTAPI_DLLEXPORT simxInt simxGetLastCmdTime();
EXTAPI_DLLEXPORT simxInt simxSynchronousTrigger();
EXTAPI_DLLEXPORT simxInt simxSynchronous(simxChar enable);
EXTAPI_DLLEXPORT simxInt simxPauseCommunication(simxChar pause);
EXTAPI_DLLEXPORT simxInt simxGetInMessageInfo(simxInt infoType,simxInt* info);
EXTAPI_DLLEXPORT simxInt simxGetOutMessageInfo(simxInt infoType,simxInt* info);
EXTAPI_DLLEXPORT simxInt simxGetConnectionId();
EXTAPI_DLLEXPORT simxChar* simxCreateBuffer(simxInt bufferSize);
EXTAPI_DLLEXPORT simxVoid simxReleaseBuffer(simxChar* buffer);
EXTAPI_DLLEXPORT simxInt simxTransferFile(const simxChar* filePathAndName,const simxChar* fileName_serverSide,simxInt timeOut,simxInt operationMode);
EXTAPI_DLLEXPORT simxInt simxEraseFile(const simxChar* fileName_serverSide,simxInt operationMode);

#endif /* _EXTAPI__ */		
