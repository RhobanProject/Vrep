# This file is part of the REMOTE API
# 
# Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
# marc@coppeliarobotics.com
# www.coppeliarobotics.com
# 
# The REMOTE API is licensed under the terms of GNU GPL:
# 
# -------------------------------------------------------------------
# The REMOTE API is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# The REMOTE API is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with the REMOTE API.  If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------------------------
#
# This file was automatically created for V-REP release V3.0.1 on January 20th 2013

import platform
from ctypes import *
from vrepConst import *

#load library
libsimx = None
if platform.system() =='Windows':
    libsimx = CDLL("./remoteApi.dll") 
elif platform.system() == 'Darwin':
    libsimx = CDLL("./remoteApi.dylib")
else:
    libsimx = CDLL("./remoteApi.so")

#ctypes wrapper prototypes 
c_GetJointPosition          = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxGetJointPosition", libsimx))
c_SetJointPosition          = CFUNCTYPE(c_int32, c_int32, c_float, c_int32)(("simxSetJointPosition", libsimx))
c_GetJointMatrix            = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxGetJointMatrix", libsimx))
c_SetSphericalJointMatrix   = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxSetSphericalJointMatrix", libsimx))
c_SetJointTargetVelocity    = CFUNCTYPE(c_int32, c_int32, c_float, c_int32)(("simxSetJointTargetVelocity", libsimx))
c_SetJointTargetPosition    = CFUNCTYPE(c_int32, c_int32, c_float, c_int32)(("simxSetJointTargetPosition", libsimx))
c_JointGetForce             = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxJointGetForce", libsimx))
c_SetJointForce             = CFUNCTYPE(c_int32, c_int32, c_float, c_int32)(("simxSetJointForce", libsimx))
c_ReadForceSensor           = CFUNCTYPE(c_int32, c_int32, POINTER(c_char), POINTER(c_float), POINTER(c_float), c_int32)(("simxReadForceSensor", libsimx))
c_BreakForceSensor          = CFUNCTYPE(c_int32, c_int32, c_int32)(("simxBreakForceSensor", libsimx))
c_ReadVisionSensor          = CFUNCTYPE(c_int32, c_int32, POINTER(c_char), POINTER(POINTER(c_float)), POINTER(POINTER(c_int32)), c_int32)(("simxReadVisionSensor", libsimx))
c_GetObjectHandle           = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_int32), c_int32)(("simxGetObjectHandle", libsimx))
c_GetVisionSensorImage      = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), POINTER(POINTER(c_byte)), c_char, c_int32)(("simxGetVisionSensorImage", libsimx))
c_SetVisionSensorImage      = CFUNCTYPE(c_int32, c_int32, POINTER(c_byte), c_int32, c_char, c_int32)(("simxSetVisionSensorImage", libsimx))
c_GetVisionSensorDepthBuffer= CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), POINTER(POINTER(c_float)), c_int32)(("simxGetVisionSensorDepthBuffer", libsimx))
c_GetObjectChild            = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetObjectChild", libsimx))
c_GetObjectParent           = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetObjectParent", libsimx))
c_ReadProximitySensor       = CFUNCTYPE(c_int32, c_int32, POINTER(c_char), POINTER(c_float), POINTER(c_int32), POINTER(c_float), c_int32)(("simxReadProximitySensor", libsimx))
c_LoadModel                 = CFUNCTYPE(c_int32, POINTER(c_char), c_char, POINTER(c_int32), c_int32)(("simxLoadModel", libsimx))
c_LoadUI                    = CFUNCTYPE(c_int32, POINTER(c_char), c_char, POINTER(c_int32), POINTER(POINTER(c_int32)), c_int32)(("simxLoadUI", libsimx))
c_LoadScene                 =  CFUNCTYPE(c_int32, POINTER(c_char), c_char, c_int32)(("simxLoadScene", libsimx))
c_StartSimulation           = CFUNCTYPE(c_int32, c_int32)(("simxStartSimulation", libsimx))
c_PauseSimulation           = CFUNCTYPE(c_int32, c_int32)(("simxPauseSimulation", libsimx))
c_StopSimulation            = CFUNCTYPE(c_int32, c_int32)(("simxStopSimulation", libsimx))
c_GetUIHandle               = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_int32), c_int32)(("simxGetUIHandle", libsimx))
c_GetUISlider               = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetUISlider", libsimx))
c_SetUISlider               = CFUNCTYPE(c_int32, c_int32, c_int32, c_int32, c_int32)(("simxSetUISlider", libsimx))
c_GetUIEventButton          = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), POINTER(c_int32), c_int32)(("simxGetUIEventButton", libsimx))
c_GetUIButtonProperty       = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetUIButtonProperty", libsimx))
c_SetUIButtonProperty       = CFUNCTYPE(c_int32, c_int32, c_int32, c_int32, c_int32)(("simxSetUIButtonProperty", libsimx))
c_AddStatusbarMessage       = CFUNCTYPE(c_int32, POINTER(c_char), c_int32)(("simxAddStatusbarMessage", libsimx))
c_AuxiliaryConsoleOpen      = CFUNCTYPE(c_int32, POINTER(c_char), c_int32, c_int32, POINTER(c_int32), POINTER(c_int32), POINTER(c_float), POINTER(c_float), POINTER(c_int32), c_int32)(("simxAuxiliaryConsoleOpen", libsimx))
c_AuxiliaryConsoleClose     = CFUNCTYPE(c_int32, c_int32, c_int32)(("simxAuxiliaryConsoleClose", libsimx))
c_AuxiliaryConsolePrint     = CFUNCTYPE(c_int32, c_int32, POINTER(c_char), c_int32)(("simxAuxiliaryConsolePrint", libsimx))
c_AuxiliaryConsoleShow      = CFUNCTYPE(c_int32, c_int32, c_char, c_int32)(("simxAuxiliaryConsoleShow", libsimx))
c_GetObjectOrientation      = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_float), c_int32)(("simxGetObjectOrientation", libsimx))
c_GetObjectPosition         = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_float), c_int32)(("simxGetObjectPosition", libsimx))
c_SetObjectOrientation      = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_float), c_int32)(("simxSetObjectOrientation", libsimx))
c_SetObjectPosition         = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_float), c_int32)(("simxSetObjectPosition", libsimx))
c_SetObjectParent           = CFUNCTYPE(c_int32, c_int32, c_int32, c_char, c_int32)(("simxSetObjectParent", libsimx))
c_SetUIButtonLabel          = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_char), POINTER(c_char), c_int32)(("simxSetUIButtonLabel", libsimx))
c_GetLastErrors             = CFUNCTYPE(c_int32, POINTER(c_int32), POINTER(POINTER(c_char)), c_int32)(("simxGetLastErrors", libsimx))
c_GetArrayParameter         = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxGetArrayParameter", libsimx))
c_SetArrayParameter         = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxSetArrayParameter", libsimx))
c_GetBooleanParameter       = CFUNCTYPE(c_int32, c_int32, POINTER(c_char), c_int32)(("simxGetBooleanParameter", libsimx))
c_SetBooleanParameter       = CFUNCTYPE(c_int32, c_int32, c_char, c_int32)(("simxSetBooleanParameter", libsimx))
c_GetIntegerParameter       = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetIntegerParameter", libsimx))
c_SetIntegerParameter       = CFUNCTYPE(c_int32, c_int32, c_int32, c_int32)(("simxSetIntegerParameter", libsimx))
c_GetFloatingParameter      = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxGetFloatingParameter", libsimx))
c_SetFloatingParameter      = CFUNCTYPE(c_int32, c_int32, c_float, c_int32)(("simxSetFloatingParameter", libsimx))
c_GetStringParameter        = CFUNCTYPE(c_int32, c_int32, POINTER(POINTER(c_char)), c_int32)(("simxGetStringParameter", libsimx))
c_GetCollisionHandle        = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_int32), c_int32)(("simxGetCollisionHandle", libsimx))
c_GetDistanceHandle         = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_int32), c_int32)(("simxGetDistanceHandle", libsimx))
c_ReadCollision             = CFUNCTYPE(c_int32, c_int32, POINTER(c_char), c_int32)(("simxReadCollision", libsimx))
c_ReadDistance              = CFUNCTYPE(c_int32, c_int32, POINTER(c_float), c_int32)(("simxReadDistance", libsimx))
c_RemoveObject              = CFUNCTYPE(c_int32, c_int32, c_int32)(("simxRemoveObject", libsimx))
c_RemoveUI                  = CFUNCTYPE(c_int32, c_int32, c_int32)(("simxRemoveUI", libsimx))
c_CloseScene                = CFUNCTYPE(c_int32, c_int32)(("simxCloseScene", libsimx))
c_GetObjects                = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), POINTER(POINTER(c_int32)), c_int32)(("simxGetObjects", libsimx))
c_DisplayDialog             = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_char), c_int32, POINTER(c_char), POINTER(c_float), POINTER(c_float), POINTER(c_int32), POINTER(c_int32), c_int32)(("simxDisplayDialog", libsimx))
c_EndDialog                 = CFUNCTYPE(c_int32, c_int32, c_int32)(("simxEndDialog", libsimx))
c_GetDialogInput            = CFUNCTYPE(c_int32, c_int32, POINTER(POINTER(c_char)), c_int32)(("simxGetDialogInput", libsimx))
c_GetDialogResult           = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetDialogResult", libsimx))
c_CopyPasteObjects          = CFUNCTYPE(c_int32, POINTER(c_int32), c_int32, POINTER(POINTER(c_int32)), POINTER(c_int32), c_int32)(("simxCopyPasteObjects", libsimx))
c_GetObjectSelection        = CFUNCTYPE(c_int32, POINTER(POINTER(c_int32)), POINTER(c_int32), c_int32)(("simxGetObjectSelection", libsimx))
c_SetObjectSelection        = CFUNCTYPE(c_int32, POINTER(c_int32), c_int32, c_int32)(("simxSetObjectSelection", libsimx))
c_ClearFloatSignal          = CFUNCTYPE(c_int32, POINTER(c_char), c_int32)(("simxClearFloatSignal", libsimx))
c_ClearIntegerSignal        = CFUNCTYPE(c_int32, POINTER(c_char), c_int32)(("simxClearIntegerSignal", libsimx))
c_ClearStringSignal         = CFUNCTYPE(c_int32, POINTER(c_char), c_int32)(("simxClearStringSignal", libsimx))
c_GetFloatSignal            = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_float), c_int32)(("simxGetFloatSignal", libsimx))
c_GetIntegerSignal          = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_int32), c_int32)(("simxGetIntegerSignal", libsimx))
c_GetStringSignal           = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(POINTER(c_char)), POINTER(c_int32), c_int32)(("simxGetStringSignal", libsimx))
c_SetFloatSignal            = CFUNCTYPE(c_int32, POINTER(c_char), c_float, c_int32)(("simxSetFloatSignal", libsimx))
c_SetIntegerSignal          = CFUNCTYPE(c_int32, POINTER(c_char), c_int32, c_int32)(("simxSetIntegerSignal", libsimx))
c_SetStringSignal           = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_char), c_int32, c_int32)(("simxSetStringSignal", libsimx))
c_GetObjectFloatParameter   = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_float), c_int32)(("simxGetObjectFloatParameter", libsimx))
c_SetObjectFloatParameter   = CFUNCTYPE(c_int32, c_int32, c_int32, c_float, c_int32)(("simxSetObjectFloatParameter", libsimx))
c_GetObjectIntParameter     = CFUNCTYPE(c_int32, c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetObjectIntParameter", libsimx))
c_SetObjectIntParameter     = CFUNCTYPE(c_int32, c_int32, c_int32, c_int32, c_int32)(("simxSetObjectIntParameter", libsimx))
c_GetModelProperty          = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32), c_int32)(("simxGetModelProperty", libsimx))
c_SetModelProperty          = CFUNCTYPE(c_int32, c_int32, c_int32, c_int32)(("simxSetModelProperty", libsimx))
c_Start                     = CFUNCTYPE(c_int32, POINTER(c_char), c_int32, c_char, c_char, c_int32)(("simxStart", libsimx))
c_Finish                    = CFUNCTYPE(None)(("simxFinish", libsimx))
c_GetPingTime               = CFUNCTYPE(c_int32, POINTER(c_int32))(("simxGetPingTime", libsimx))
c_GetLastCmdTime            = CFUNCTYPE(c_int32)(("simxGetLastCmdTime", libsimx))
c_SynchronousTrigger        = CFUNCTYPE(c_int32)(("simxSynchronousTrigger", libsimx))
c_Synchronous               = CFUNCTYPE(c_int32, c_char)(("simxSynchronous", libsimx))
c_PauseCommunication        = CFUNCTYPE(c_int32, c_char)(("simxPauseCommunication", libsimx))
c_GetInMessageInfo          = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32))(("simxGetInMessageInfo", libsimx))
c_GetOutMessageInfo         = CFUNCTYPE(c_int32, c_int32, POINTER(c_int32))(("simxGetOutMessageInfo", libsimx))
c_GetConnectionId           = CFUNCTYPE(c_int32)(("simxGetConnectionId", libsimx))
c_CreateBuffer              = CFUNCTYPE(POINTER(c_char), c_int32)(("simxCreateBuffer", libsimx))
c_ReleaseBuffer             = CFUNCTYPE(None, c_void_p)(("simxReleaseBuffer", libsimx))
c_TransferFile              = CFUNCTYPE(c_int32, POINTER(c_char), POINTER(c_char), c_int32, c_int32)(("simxTransferFile", libsimx))
c_EraseFile                 = CFUNCTYPE(c_int32, POINTER(c_char), c_int32)(("simxEraseFile", libsimx))

#API functions
def simxGetJointPosition(jointHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    position = c_float()
    return c_GetJointPosition(jointHandle, byref(position), operationMode), position.value

def simxSetJointPosition(jointHandle, position, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetJointPosition(jointHandle, position, operationMode)

def simxGetJointMatrix(jointHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    matrix = (c_float*12)()
    ret = c_GetJointMatrix(jointHandle, matrix, operationMode)	
    arr = []
    for i in range(12):
        arr.append(matrix[i])	
    return ret, arr

def simxSetSphericalJointMatrix(jointHandle, matrix, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    matrix = (c_float*12)(*matrix)
    return c_SetSphericalJointMatrix(jointHandle, matrix, operationMode)

def simxSetJointTargetVelocity(jointHandle, targetVelocity, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetJointTargetVelocity(jointHandle, targetVelocity, operationMode)

def simxSetJointTargetPosition(jointHandle, targetPosition, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetJointTargetPosition(jointHandle, targetPosition, operationMode)

def simxJointGetForce(jointHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    force = c_float()
    return c_JointGetForce(jointHandle, byref(force), operationMode), force.value

def simxSetJointForce(jointHandle, force, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    return c_SetJointForce(jointHandle, force, operationMode)

def simxReadForceSensor(forceSensorHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    state = c_char()
    forceVector  = (c_float*3)()
    torqueVector = (c_float*3)()
    ret = c_ReadForceSensor(forceSensorHandle, byref(state), forceVector, torqueVector, operationMode)
    arr1 = []
    for i in range(3):
        arr1.append(forceVector[i])	
    arr2 = []
    for i in range(3):
        arr2.append(torqueVector[i])	
    return ret, ord(state.value), arr1, arr2 

def simxBreakForceSensor(forceSensorHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    return c_BreakForceSensor(forceSensorHandle, operationMode)

def simxReadVisionSensor(sensorHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    detectionState = c_char()
    auxValues      = pointer(c_float())
    auxValuesCount = pointer(c_int())
    ret = c_ReadVisionSensor(sensorHandle, byref(detectionState), byref(auxValues), byref(auxValuesCount), operationMode)
    
    auxValues2 = []
    if ret == 0:
        s = 0
        for i in range(auxValuesCount[0]):
            auxValues2.append(auxValues[s:s+auxValuesCount[i+1]])
            s += auxValuesCount[i+1]

        #free C buffers
        c_ReleaseBuffer(auxValues)
        c_ReleaseBuffer(auxValuesCount)

    return ret, bool(detectionState.value!='\0'), auxValues2 

def simxGetObjectHandle(objectName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    handle = c_int()
    return c_GetObjectHandle(objectName, byref(handle), operationMode), handle.value

def simxGetVisionSensorImage(sensorHandle, options, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    resolution = (c_int*2)()
    c_image  = pointer(c_byte())
    bytesPerPixel = 3
    if (options and 1) != 0:
        bytesPerPixel = 1	
    ret = c_GetVisionSensorImage(sensorHandle, resolution, byref(c_image), chr(options), operationMode)

    reso = []
    image = []
    if (ret == 0):	
        image = [None]*resolution[0]*resolution[1]*bytesPerPixel
        for i in range(resolution[0] * resolution[1] * bytesPerPixel):
            image[i] = c_image[i]
        for i in range(2):
            reso.append(resolution[i])
    return ret, reso, image

def simxSetVisionSensorImage(sensorHandle, image, options, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    size = len(image)
    image_bytes  = (c_byte*size)(*image)
    return c_SetVisionSensorImage(sensorHandle, image_bytes, size, chr(options), operationMode)

def simxGetVisionSensorDepthBuffer(sensorHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    c_buffer  = pointer(c_float())
    resolution = (c_int*2)()
    ret = c_GetVisionSensorDepthBuffer(sensorHandle, resolution, byref(c_buffer), operationMode)
    reso = []
    buffer = []
    if (ret == 0):	
        buffer = [None]*resolution[0]*resolution[1]
        for i in range(resolution[0] * resolution[1]):
            buffer[i] = c_buffer[i]
        for i in range(2):
            reso.append(resolution[i])
    return ret, reso, buffer

def simxGetObjectChild(parentObjectHandle, childIndex, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    childObjectHandle = c_int()
    return c_GetObjectChild(parentObjectHandle, childIndex, byref(childObjectHandle), operationMode), childObjectHandle.value

def simxGetObjectParent(childObjectHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    parentObjectHandle = c_int()
    return c_GetObjectParent(childObjectHandle, byref(parentObjectHandle), operationMode), parentObjectHandle.value

def simxReadProximitySensor(sensorHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    detectionState = c_char()
    detectedObjectHandle = c_int()
    detectedPoint  = (c_float*3)()
    detectedSurfaceNormalVector = (c_float*3)()
    ret = c_ReadProximitySensor(sensorHandle, byref(detectionState), detectedPoint, byref(detectedObjectHandle), detectedSurfaceNormalVector, operationMode)
    arr1 = []
    for i in range(3):
        arr1.append(detectedPoint[i])	
    arr2 = []
    for i in range(3):
        arr2.append(detectedSurfaceNormalVector[i])	
    return ret, bool(detectionState.value!='\0'), arr1, detectedObjectHandle.value, arr2

def simxLoadModel(modelPathAndName, options, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    baseHandle = c_int()
    return c_LoadModel(modelPathAndName, chr(options), byref(baseHandle), operationMode), baseHandle.value

def simxLoadUI(uiPathAndName, options, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    count = c_int()
    uiHandles = pointer(c_int())
    ret = c_LoadUI(uiPathAndName, chr(options), byref(count), byref(uiHandles), operationMode)
    
    handles = []
    if ret == 0:
        for i in range(count.value):
            handles.append(uiHandles[i])
        #free C buffers
        c_ReleaseBuffer(uiHandles)

    return ret, handles

def simxLoadScene(scenePathAndName, options, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_LoadScene(scenePathAndName, chr(options), operationMode)

def simxStartSimulation(operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_StartSimulation(operationMode)

def simxPauseSimulation(operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_PauseSimulation(operationMode)

def simxStopSimulation(operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_StopSimulation(operationMode)

def simxGetUIHandle(uiName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    handle = c_int()
    return c_GetUIHandle(uiName, byref(handle), operationMode), handle.value

def simxGetUISlider(uiHandle, uiButtonID, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    position = c_int()
    return c_GetUISlider(uiHandle, uiButtonID, byref(position), operationMode), position.value

def simxSetUISlider(uiHandle, uiButtonID, position, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetUISlider(uiHandle, uiButtonID, position, operationMode)

def simxGetUIEventButton(uiHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    uiEventButtonID = c_int()
    auxValues = (c_int*2)()
    ret = c_GetUIEventButton(uiHandle, byref(uiEventButtonID), auxValues, operationMode)
    arr = []
    for i in range(2):
        arr.append(auxValues[i])	
    return ret, uiEventButtonID.value, arr

def simxGetUIButtonProperty(uiHandle, uiButtonID, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    prop = c_int()
    return c_GetUIButtonProperty(uiHandle, uiButtonID, byref(prop), operationMode), prop.value

def simxSetUIButtonProperty(uiHandle, uiButtonID, prop, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    
    return c_SetUIButtonProperty(uiHandle, uiButtonID, prop, operationMode)

def simxAddStatusbarMessage(message, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_AddStatusbarMessage(message, operationMode)

def simxAuxiliaryConsoleOpen(title, maxLines, mode, position, size, textColor, backgroundColor, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    consoleHandle = c_int()
    if position != None:
        c_position = (c_int*2)(*position)
    else:
        c_position = None
    if size != None:
        c_size = (c_int*2)(*size)
    else:
        c_size = None
    if textColor != None:
        c_textColor = (c_float*3)(*textColor)
    else:
        c_textColor = None
    if backgroundColor != None:
        c_backgroundColor = (c_float*3)(*backgroundColor)
    else:
        c_backgroundColor = None
    return c_AuxiliaryConsoleOpen(title, maxLines, mode, c_position, c_size, c_textColor, c_backgroundColor, byref(consoleHandle), operationMode), consoleHandle.value

def simxAuxiliaryConsoleClose(consoleHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_AuxiliaryConsoleClose(consoleHandle, operationMode)

def simxAuxiliaryConsolePrint(consoleHandle, txt, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_AuxiliaryConsolePrint(consoleHandle, txt, operationMode)

def simxAuxiliaryConsoleShow(consoleHandle, showState, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_AuxiliaryConsoleShow(consoleHandle, chr(showState), operationMode)

def simxGetObjectOrientation(objectHandle, relativeToObjectHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    eulerAngles = (c_float*3)()
    ret = c_GetObjectOrientation(objectHandle, relativeToObjectHandle, eulerAngles, operationMode)
    arr = []
    for i in range(3):
        arr.append(eulerAngles[i])	
    return ret, arr

def simxGetObjectPosition(objectHandle, relativeToObjectHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    position = (c_float*3)()
    ret = c_GetObjectPosition(objectHandle, relativeToObjectHandle, position, operationMode)
    arr = []
    for i in range(3):
        arr.append(position[i])	
    return ret, arr

def simxSetObjectOrientation(objectHandle, relativeToObjectHandle, eulerAngles, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    angles = (c_float*3)(*eulerAngles)
    return c_SetObjectOrientation(objectHandle, relativeToObjectHandle, angles, operationMode)

def simxSetObjectPosition(objectHandle, relativeToObjectHandle, position, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    c_position = (c_float*3)(*position)
    return c_SetObjectPosition(objectHandle, relativeToObjectHandle, c_position, operationMode)

def simxSetObjectParent(objectHandle, parentObject, keepInPlace, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetObjectParent(objectHandle, parentObject, chr(keepInPlace), operationMode)

def simxSetUIButtonLabel(uiHandle, uiButtonID, upStateLabel, downStateLabel, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetUIButtonLabel(uiHandle, uiButtonID, upStateLabel, downStateLabel, operationMode)

def simxGetLastErrors(operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    errors =[]
    errorCnt = c_int()
    errorStrings = pointer(c_char())
    ret = c_GetLastErrors(byref(errorCnt), byref(errorStrings), operationMode)
    
    if ret == 0:
        s = 0
        for i in range(errorCnt.value):
            a = bytearray()
            while errorStrings[s] != '\0':
                a.append(errorStrings[s])
                s += 1
                
            s += 1 #skip null
            errors.append(str(a))

    return ret, errors

def simxGetArrayParameter(paramIdentifier, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    paramValues = (c_float*3)()
    ret = c_GetArrayParameter(paramIdentifier, paramValues, operationMode)
    arr = []
    for i in range(3):
        arr.append(paramValues[i])	
    return ret, arr

def simxSetArrayParameter(paramIdentifier, paramValues, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    c_paramValues = (c_float*3)(*paramValues)
    return c_SetArrayParameter(paramIdentifier, c_paramValues, operationMode)

def simxGetBooleanParameter(paramIdentifier, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    paramValue = c_char()
    return c_GetBooleanParameter(paramIdentifier, byref(paramValue), operationMode), bool(paramValue.value!='\0')

def simxSetBooleanParameter(paramIdentifier, paramValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetBooleanParameter(paramIdentifier, chr(paramValue), operationMode)

def simxGetIntegerParameter(paramIdentifier, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    paramValue = c_int()
    return c_GetIntegerParameter(paramIdentifier, byref(paramValue), operationMode), paramValue.value

def simxSetIntegerParameter(paramIdentifier, paramValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetIntegerParameter(paramIdentifier, paramValue, operationMode)

def simxGetFloatingParameter(paramIdentifier, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    paramValue = c_float()
    return c_GetFloatingParameter(paramIdentifier, byref(paramValue), operationMode), paramValue.value

def simxSetFloatingParameter(paramIdentifier, paramValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetFloatingParameter(paramIdentifier, paramValue, operationMode)

def simxGetStringParameter(paramIdentifier, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    paramValue = pointer(c_char())
    ret = c_GetStringParameter(paramIdentifier, byref(paramValue), operationMode)
    
    a = bytearray()
    if ret == 0:
        i = 0
        while paramValue[i] != '\0':
            a.append(paramValue[i])
            i=i+1

    return ret, str(a)

def simxGetCollisionHandle(collisionObjectName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    handle = c_int()
    return c_GetCollisionHandle(collisionObjectName, byref(handle), operationMode), handle.value

def simxGetDistanceHandle(distanceObjectName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    handle = c_int()
    return c_GetDistanceHandle(distanceObjectName, byref(handle), operationMode), handle.value

def simxReadCollision(collisionObjectHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    collisionState = c_char()
    return c_ReadCollision(collisionObjectHandle, byref(collisionState), operationMode), bool(collisionState.value!='\0')

def simxReadDistance(distanceObjectHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    minimumDistance = c_float()
    return c_ReadDistance(distanceObjectHandle, byref(minimumDistance), operationMode), minimumDistance.value

def simxRemoveObject(objectHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_RemoveObject(objectHandle, operationMode)

def simxRemoveUI(uiHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_RemoveUI(uiHandle, operationMode)

def simxCloseScene(operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_CloseScene(operationMode)

def simxGetObjects(objectType, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    objectCount = c_int()
    objectHandles = pointer(c_int())

    ret = c_GetObjects(objectType, byref(objectCount), byref(objectHandles), operationMode)
    handles = []
    if ret == 0:
        for i in range(objectCount.value):
            handles.append(objectHandles[i])

    return ret, handles


def simxDisplayDialog(titleText, mainText, dialogType, initialText, titleColors, dialogColors, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    if titleColors != None:
        c_titleColors  = (c_float*6)(*titleColors)
    else:
        c_titleColors  = None
    if dialogColors != None:
        c_dialogColors  = (c_float*6)(*dialogColors)
    else:
        c_dialogColors  = None

    c_dialogHandle = c_int()
    c_uiHandle = c_int()
    return c_DisplayDialog(titleText, mainText, dialogType, initialText, c_titleColors, c_dialogColors, byref(c_dialogHandle), byref(c_uiHandle), operationMode), c_dialogHandle.value, c_uiHandle.value

def simxEndDialog(dialogHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_EndDialog(dialogHandle, operationMode)

def simxGetDialogInput(dialogHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    inputText = pointer(c_char())
    ret = c_GetDialogInput(dialogHandle, byref(inputText), operationMode)
    
    a = bytearray()
    if ret == 0:
        i = 0
        while inputText[i] != '\0':
            a.append(inputText[i])
            i = i+1
			
    return ret, str(a)


def simxGetDialogResult(dialogHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    result = c_int()
    return c_GetDialogResult(dialogHandle, byref(result), operationMode), result.value

def simxCopyPasteObjects(objectHandles, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    c_objectHandles  = (c_int*len(objectHandles))(*objectHandles)
    newObjectCount   = c_int()
    newObjectHandles = pointer(c_int())
    ret = c_CopyPasteObjects(c_objectHandles, len(objectHandles), byref(newObjectHandles), byref(newObjectCount), operationMode)

    newobj = []
    if ret == 0:
        for i in range(newObjectCount.value):
            newobj.append(newObjectHandles[i])

    return ret, newobj


def simxGetObjectSelection(operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    objectCount   = c_int()
    objectHandles = pointer(c_int())
    ret = c_GetObjectSelection(byref(objectHandles), byref(objectCount), operationMode)

    newobj = []
    if ret == 0:
        for i in range(objectCount.value):
            newobj.append(objectHandles[i])

    return ret, newobj



def simxSetObjectSelection(objectHandles, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    c_objectHandles  = (c_int*len(objectHandles))(*objectHandles)
    return c_SetObjectSelection(c_objectHandles, len(objectHandles), operationMode)

def simxClearFloatSignal(signalName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_ClearFloatSignal(signalName, operationMode)

def simxClearIntegerSignal(signalName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_ClearIntegerSignal(signalName, operationMode)

def simxClearStringSignal(signalName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_ClearStringSignal(signalName, operationMode)

def simxGetFloatSignal(signalName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    signalValue = c_float()
    return c_GetFloatSignal(signalName, byref(signalValue), operationMode), signalValue.value

def simxGetIntegerSignal(signalName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    signalValue = c_int()
    return c_GetIntegerSignal(signalName, byref(signalValue), operationMode), signalValue.value

def simxGetStringSignal(signalName, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    signalLength = c_int();
    signalValue = pointer(c_char())
    ret = c_GetStringSignal(signalName, byref(signalValue), byref(signalLength), operationMode)

    a = bytearray()
    if ret == 0:
        for i in range(signalLength.value):
            a.append(signalValue[i])

    return ret, str(a)

def simxSetFloatSignal(signalName, signalValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetFloatSignal(signalName, signalValue, operationMode)

def simxSetIntegerSignal(signalName, signalValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetIntegerSignal(signalName, signalValue, operationMode)

def simxSetStringSignal(signalName, signalValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetStringSignal(signalName, signalValue, len(signalValue), operationMode)

def simxGetObjectFloatParameter(objectHandle, parameterID, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    
    parameterValue = c_float()
    return c_GetObjectFloatParameter(objectHandle, parameterID, byref(parameterValue), operationMode), parameterValue.value 

def simxSetObjectFloatParameter(objectHandle, parameterID, parameterValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetObjectFloatParameter(objectHandle, parameterID, parameterValue, operationMode)

def simxGetObjectIntParameter(objectHandle, parameterID, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    parameterValue = c_int() 
    return c_GetObjectIntParameter(objectHandle, parameterID, byref(parameterValue), operationMode), parameterValue.value

def simxSetObjectIntParameter(objectHandle, parameterID, parameterValue, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetObjectIntParameter(objectHandle, parameterID, parameterValue, operationMode)

def simxGetModelProperty(objectHandle, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    prop = c_int()
    return c_GetModelProperty(objectHandle, byref(prop), operationMode), prop.value

def simxSetModelProperty(objectHandle, prop, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SetModelProperty(objectHandle, prop, operationMode)

def simxStart(connectionAddress, connectionPort, waitUntilConnected, doNotReconnectOnceDisconnected, timeOutInMs):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_Start(connectionAddress, connectionPort, chr(waitUntilConnected), chr(doNotReconnectOnceDisconnected), timeOutInMs)

def simxFinish():
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_Finish()

def simxGetPingTime():
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    pingTime = c_int()
    return c_GetPingTime(byref(pingTime)), pingTime.value

def simxGetLastCmdTime():
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_GetLastCmdTime()

def simxSynchronousTrigger():
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_SynchronousTrigger()

def simxSynchronous(enable):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_Synchronous(chr(enable))

def simxPauseCommunication(enable):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_PauseCommunication(chr(enable))

def simxGetInMessageInfo(infoType):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    info = c_int()
    return c_GetInMessageInfo(infoType, byref(info)), info.value

def simxGetOutMessageInfo(infoType):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''
    info = c_int()
    return c_GetOutMessageInfo(infoType, byref(info)), info.value

def simxGetConnectionId():
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_GetConnectionId()

def simxCreateBuffer(bufferSize):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_CreateBuffer(bufferSize)

def simxReleaseBuffer(buffer):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_ReleaseBuffer(buffer)

def simxTransferFile(filePathAndName, fileName_serverSide, timeOut, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_TransferFile(filePathAndName, fileName_serverSide, timeOut, operationMode)

def simxEraseFile(fileName_serverSide, operationMode):
    '''
    Please have a look at the function description/documentation in the V-REP user manual
    '''

    return c_EraseFile(fileName_serverSide, operationMode)

