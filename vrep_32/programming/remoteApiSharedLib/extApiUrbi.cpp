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

#include <urbi/uobject.hh>

extern "C" {
#include "extApi.h"
}


using namespace urbi;
class vrep: public urbi::UObject // Must inherit from UObject.
{ 
    public: 
        // The class must have a single const  ructor taking a string. 
       vrep (const std::string &s):UObject(s) {
            UBindFunction(vrep ,simxGetJointPosition);
            UBindFunction(vrep ,simxSetJointPosition);
            UBindFunction(vrep ,simxGetJointMatrix);
            UBindFunction(vrep ,simxSetSphericalJointMatrix);
            UBindFunction(vrep ,simxSetJointTargetVelocity);
            UBindFunction(vrep ,simxSetJointTargetPosition);
            UBindFunction(vrep ,simxJointGetForce);
            UBindFunction(vrep ,simxSetJointForce);
            UBindFunction(vrep ,simxReadForceSensor);
            UBindFunction(vrep ,simxBreakForceSensor);
            UBindFunction(vrep ,simxReadVisionSensor);
            UBindFunction(vrep ,simxGetObjectHandle);
            UBindFunction(vrep ,simxGetVisionSensorImage);
            UBindFunction(vrep ,simxSetVisionSensorImage);
            UBindFunction(vrep ,simxGetVisionSensorDepthBuffer);
            UBindFunction(vrep ,simxGetObjectChild);
            UBindFunction(vrep ,simxGetObjectParent);
            UBindFunction(vrep ,simxReadProximitySensor);
            UBindFunction(vrep ,simxLoadModel);
            UBindFunction(vrep ,simxLoadUI);
            UBindFunction(vrep ,simxLoadScene);
            UBindFunction(vrep ,simxStartSimulation);
            UBindFunction(vrep ,simxPauseSimulation);
            UBindFunction(vrep ,simxStopSimulation);
            UBindFunction(vrep ,simxGetUIHandle);
            UBindFunction(vrep ,simxGetUISlider);
            UBindFunction(vrep ,simxSetUISlider);
            UBindFunction(vrep ,simxGetUIEventButton);
            UBindFunction(vrep ,simxGetUIButtonProperty);
            UBindFunction(vrep ,simxSetUIButtonProperty);
            UBindFunction(vrep ,simxAddStatusbarMessage);
            UBindFunction(vrep ,simxAuxiliaryConsoleOpen);
            UBindFunction(vrep ,simxAuxiliaryConsoleClose);
            UBindFunction(vrep ,simxAuxiliaryConsolePrint);
            UBindFunction(vrep ,simxAuxiliaryConsoleShow);
            UBindFunction(vrep ,simxGetObjectOrientation);
            UBindFunction(vrep ,simxGetObjectPosition);
            UBindFunction(vrep ,simxSetObjectOrientation);
            UBindFunction(vrep ,simxSetObjectPosition);
            UBindFunction(vrep ,simxSetObjectParent);
            UBindFunction(vrep ,simxSetUIButtonLabel);
            UBindFunction(vrep ,simxGetLastErrors);
            UBindFunction(vrep ,simxGetArrayParameter);
            UBindFunction(vrep ,simxSetArrayParameter);            
            UBindFunction(vrep ,simxGetBooleanParameter);
            UBindFunction(vrep ,simxSetBooleanParameter);
            UBindFunction(vrep ,simxGetIntegerParameter);
            UBindFunction(vrep ,simxSetIntegerParameter);
            UBindFunction(vrep ,simxGetFloatingParameter);
            UBindFunction(vrep ,simxSetFloatingParameter);
            UBindFunction(vrep ,simxGetStringParameter);
            UBindFunction(vrep ,simxGetCollisionHandle);
            UBindFunction(vrep ,simxGetDistanceHandle);
            UBindFunction(vrep ,simxReadCollision);
            UBindFunction(vrep ,simxReadDistance);
            UBindFunction(vrep ,simxRemoveObject);
            UBindFunction(vrep ,simxRemoveUI);
            UBindFunction(vrep ,simxCloseScene);
            UBindFunction(vrep ,simxGetObjects);
            UBindFunction(vrep ,simxDisplayDialog);
            UBindFunction(vrep ,simxEndDialog);
            UBindFunction(vrep ,simxGetDialogInput);
            UBindFunction(vrep ,simxGetDialogResult);
            UBindFunction(vrep ,simxCopyPasteObjects);
            UBindFunction(vrep ,simxGetObjectSelection);
            UBindFunction(vrep ,simxSetObjectSelection);
            UBindFunction(vrep ,simxClearFloatSignal);
            UBindFunction(vrep ,simxClearIntegerSignal);
            UBindFunction(vrep ,simxClearStringSignal);
            UBindFunction(vrep ,simxGetFloatSignal);
            UBindFunction(vrep ,simxGetIntegerSignal);
            UBindFunction(vrep ,simxGetStringSignal);
            UBindFunction(vrep ,simxSetFloatSignal);
            UBindFunction(vrep ,simxSetIntegerSignal);
            UBindFunction(vrep ,simxSetStringSignal);
            UBindFunction(vrep ,simxGetObjectFloatParameter);
            UBindFunction(vrep ,simxSetObjectFloatParameter);
            UBindFunction(vrep ,simxGetObjectIntParameter);
            UBindFunction(vrep ,simxSetObjectIntParameter);
            UBindFunction(vrep ,simxGetModelProperty);
            UBindFunction(vrep ,simxSetModelProperty);
            UBindFunction(vrep ,simxStart);
            UBindFunction(vrep ,simxFinish);
            UBindFunction(vrep ,simxGetPingTime);
            UBindFunction(vrep ,simxGetLastCmdTime);
            UBindFunction(vrep ,simxSynchronousTrigger);
            UBindFunction(vrep ,simxSynchronous);
            UBindFunction(vrep ,simxPauseCommunication);
            UBindFunction(vrep ,simxGetInMessageInfo);
            UBindFunction(vrep ,simxGetOutMessageInfo);
            UBindFunction(vrep ,simxGetConnectionId);
            UBindFunction(vrep ,simxTransferFile);
            UBindFunction(vrep ,simxEraseFile);



        }
        UList simxGetJointPosition (simxInt jointHandle, simxInt operationMode) {
            UList result;
            simxFloat position;
            result.push_back(::simxGetJointPosition(jointHandle, &position, operationMode));
            result.push_back(position);
            return result;
        }

        simxInt simxSetJointPosition (simxInt jointHandle, ufloat position, simxInt operationMode) {
            return ::simxSetJointPosition(jointHandle, position, operationMode);
        }

        UList simxGetJointMatrix (simxInt jointHandle, simxInt operationMode) {
            int i;
            UList       matrix;
            UList result;
            simxFloat   c_matrix[12];

            result.push_back(::simxGetJointMatrix(jointHandle, c_matrix, operationMode));
            for (i=0; i<12; i++) {
                matrix.push_back((ufloat)c_matrix[i]);
            }
            result.push_back(matrix);
            return result;
        }

        UList simxSetSphericalJointMatrix (simxInt jointHandle, UList matrix, simxInt operationMode) {
            int i;
            UList result;
            simxFloat   c_matrix[12];

            for (i=0; i<12; i++) {
                c_matrix[i] = (ufloat)matrix[i];
            }
            result.push_back(::simxSetSphericalJointMatrix(jointHandle, c_matrix, operationMode));
            return result;
        }

        simxInt simxSetJointTargetVelocity (simxInt jointHandle, ufloat targetVelocity, simxInt operationMode) {
            return ::simxSetJointTargetVelocity(jointHandle, targetVelocity, operationMode);
        }

        simxInt simxSetJointTargetPosition (simxInt jointHandle, ufloat targetPosition, simxInt operationMode) {
            return ::simxSetJointTargetPosition(jointHandle, targetPosition, operationMode);
        }

        UList simxJointGetForce (simxInt jointHandle, simxInt operationMode) {
            UList result;
            simxFloat force;
            result.push_back(::simxJointGetForce(jointHandle, &force, operationMode));
            result.push_back(force);
            return result;
        }
 
        simxInt simxSetJointForce (simxInt jointHandle, ufloat force, simxInt operationMode) {
            return ::simxSetJointForce(jointHandle, force, operationMode);
        }

        UList simxReadForceSensor (simxInt forceSensorHandle, simxInt operationMode) {
            int i;
            simxChar state;
            UList result;            
            UList forceVector;
            UList torqueVector;

            simxFloat c_forceVector[3];
            simxFloat c_torqueVector[3];

            result.push_back(::simxReadForceSensor(forceSensorHandle, &state, c_forceVector, c_torqueVector, operationMode));

            for (i=0; i<3; i++) {
                forceVector.push_back((ufloat)c_forceVector[i]);
                torqueVector.push_back((ufloat)c_torqueVector[i]);
            }
            result.push_back((int) state);
            result.push_back(forceVector);
            result.push_back(torqueVector);
            return result;
        }

        simxInt simxBreakForceSensor (simxInt forceSensorHandle, simxInt operationMode) {
            return ::simxBreakForceSensor(forceSensorHandle, operationMode);
        }

        UList simxReadVisionSensor (simxInt sensorHandle, simxInt operationMode) {
            int i,x,ret, offset;
            UList values;
            UList result;
            simxChar    detectionState;
            simxFloat   *auxValues;
            simxInt     *auxValuesCount;

            ret = ::simxReadVisionSensor(sensorHandle, &detectionState, &auxValues, &auxValuesCount, operationMode);
            if (ret==0) {
                offset = 0;
                for (i=0; i<auxValuesCount[0]; i++) {
					UList packet;

                    for (x=0; x<auxValuesCount[i+1]; x++) {
                        packet.push_back(auxValues[offset+x]);
                    }
					values.push_back(packet);
                    offset += auxValuesCount[i+1];
                }
	            simxReleaseBuffer((simxChar*)auxValues);
		        simxReleaseBuffer((simxChar*)auxValuesCount);
            }

            result.push_back(ret);
            result.push_back((int) detectionState);
            result.push_back(values);

            return result;
        }

        UList simxGetObjectHandle (const simxChar* objectName, simxInt operationMode) {
            UList result;
            simxInt handle;
            result.push_back(::simxGetObjectHandle(objectName, &handle, operationMode));
            result.push_back(handle);
            return result;
        }

        UList simxGetVisionSensorImage (simxInt sensorHandle, int options, simxInt operationMode) {
            int i, ret;
            simxChar *c_image;
            simxInt resolution[2];
			simxInt bpp=3;
			if (options&1)
				bpp=1; // greyscale

            UImage image;
            UList result;

            ret = ::simxGetVisionSensorImage(sensorHandle, resolution, &c_image, (simxChar)options, operationMode);
			if (ret==0)
			{
	            image.data   = (unsigned char*)c_image;
	            image.width  = resolution[0];
		        image.height = resolution[1];
				image.size = resolution[0]*resolution[1]*bpp;
				if (options&1)
					image.imageFormat = IMAGE_GREY8;
				else
					image.imageFormat = IMAGE_RGB;
			}
			else
			{
	            image.data=NULL;
	            image.width=0;
		        image.height=0;
				image.size=0;
				image.imageFormat=IMAGE_UNKNOWN;
			}
            result.push_back(ret);
            result.push_back(image);
            return result;
        }

        simxInt simxSetVisionSensorImage (simxInt sensorHandle, UImage image, simxInt operationMode) {
			simxInt options=0;
			simxInt bpp=3;
			if (image.imageFormat == IMAGE_GREY8)
			{
				options|=1;
				bpp=1;
			}
			else
			{
				if (image.imageFormat != IMAGE_RGB)
					return simx_error_local_error_flag;

			}

            return ::simxSetVisionSensorImage(sensorHandle,(simxChar*) image.data, image.width*image.height*bpp, (simxChar) options, operationMode);
        }

        UList simxGetVisionSensorDepthBuffer (simxInt sensorHandle, simxInt operationMode) {
            int i, ret;
            simxFloat *c_buffer;
            simxInt resolution[2];
            
            UImage image;
//            UList buffer;
//            UList reso;
            UList result;

            ret = ::simxGetVisionSensorDepthBuffer(sensorHandle, resolution, &c_buffer, operationMode);
			if (ret==0)
			{
	            image.data   = (unsigned char*)c_buffer;
	            image.width  = resolution[0];
		        image.height = resolution[1];
				image.size = resolution[0]*resolution[1]*4;
				image.imageFormat = IMAGE_UNKNOWN;
			}
			else
			{
	            image.data=NULL;
	            image.width=0;
		        image.height=0;
				image.size=0;
				image.imageFormat=IMAGE_UNKNOWN;
			}
            result.push_back(ret);
            result.push_back(image);
/*
			if (ret == 0) {
                for (i=0; i<resolution[0]*resolution[1]; i++) {
                    buffer.push_back(c_buffer[i]);
                }
				reso.push_back(resolution[0]);
				reso.push_back(resolution[1]);
            }
            result.push_back(ret);
            result.push_back(reso);
            result.push_back(buffer);
			*/
            return result;
        }

        UList simxGetObjectChild (simxInt parentObjectHandle, simxInt childIndex, simxInt operationMode) {
            UList result;
            simxInt childObjectHandle;
            result.push_back(::simxGetObjectChild(parentObjectHandle, childIndex, &childObjectHandle, operationMode));
            result.push_back(childObjectHandle);
            return result;
        }

        UList simxGetObjectParent (simxInt childObjectHandle, simxInt operationMode) {
            UList result;
            simxInt parentObjectHandle;
            result.push_back(::simxGetObjectParent(childObjectHandle, &parentObjectHandle, operationMode));
            result.push_back(parentObjectHandle);
            return result;
        }

        UList simxReadProximitySensor (simxInt sensorHandle, simxInt operationMode) {
            int i, ret;
            simxChar  detectionState;
            simxFloat c_detectedPoint[3];
            simxInt detectedObjectHandle;
            simxFloat c_detectedSurfaceNormalVector[3];

            UList result;
            UList detectedPoint;
            UList detectedSurfaceNormalVector;

            ret = ::simxReadProximitySensor(sensorHandle, &detectionState, c_detectedPoint, &detectedObjectHandle, c_detectedSurfaceNormalVector, operationMode);
            if (ret == 0) {
                for (i=0; i<3; i++) {
                    detectedPoint.push_back(c_detectedPoint[i]);
                    detectedSurfaceNormalVector.push_back(c_detectedSurfaceNormalVector[i]);
                }
            }

            result.push_back(ret);
            result.push_back((int) detectionState);
            result.push_back(detectedPoint);
            result.push_back(detectedObjectHandle);
            result.push_back(detectedSurfaceNormalVector);
            return result;
        }

        UList simxLoadModel (const simxChar* modelPathAndName, int options, simxInt operationMode) {
            UList result;
            simxInt baseHandle;
            result.push_back(::simxLoadModel(modelPathAndName, (simxChar) options, &baseHandle, operationMode));
            result.push_back(baseHandle);
            return result;
        }

        UList simxLoadUI (const simxChar* uiPathAndName, int options, simxInt operationMode) {
            int i, ret;
            simxInt count;
            simxInt *c_uiHandles;
            
            UList uiHandles;
            UList result;

            ret = ::simxLoadUI(uiPathAndName, (simxChar) options, &count, &c_uiHandles, operationMode);
            if (ret == 0) {
                for (i=0; i<count; i++) {
                    uiHandles.push_back(c_uiHandles[i]);
                }
				simxReleaseBuffer((simxChar*)c_uiHandles);
            }
            result.push_back(ret);
            result.push_back(uiHandles);
            return result;
        }

        simxInt simxLoadScene (const simxChar* scenePathAndName, int options, simxInt operationMode) {
            return ::simxLoadScene(scenePathAndName, (simxChar) options, operationMode);
        }

        simxInt simxStartSimulation (simxInt operationMode) {
            return ::simxStartSimulation(operationMode);
        }

        simxInt simxPauseSimulation (simxInt operationMode) {
            return ::simxPauseSimulation(operationMode);
        }

        simxInt simxStopSimulation (simxInt operationMode) {
            return ::simxStopSimulation(operationMode);
        }

        UList simxGetUIHandle (const simxChar* uiName, simxInt operationMode) {
            UList result;
            simxInt handle;
            result.push_back(::simxGetUIHandle(uiName, &handle, operationMode));
            result.push_back(handle);
            return result;
        }

        UList simxGetUISlider (simxInt uiHandle, simxInt uiButtonID, simxInt operationMode) {
            UList result;
            simxInt position;
            result.push_back(::simxGetUISlider(uiHandle, uiButtonID, &position, operationMode));
            result.push_back(position);
            return result;
        }

        simxInt simxSetUISlider (simxInt uiHandle, simxInt uiButtonID, simxInt position, simxInt operationMode) {
            return ::simxSetUISlider(uiHandle, uiButtonID, position, operationMode);
        }

        UList simxGetUIEventButton (simxInt uiHandle, simxInt operationMode) {
            int i, ret;
            simxInt c_auxValues[2];
            simxInt uiEventButtonID;

            UList auxValues;
            UList result;

            ret = ::simxGetUIEventButton(uiHandle, &uiEventButtonID, c_auxValues, operationMode);
            if (ret == 0) {
                for (i=0; i<2; i++) {
                    auxValues.push_back(c_auxValues[i]);
                }
            }

            result.push_back(ret);
            result.push_back(uiEventButtonID);
            result.push_back(auxValues);
            return result;
        }

        UList simxGetUIButtonProperty (simxInt uiHandle, simxInt uiButtonID, simxInt operationMode) {
            simxInt prop;
            UList result;

            result.push_back(::simxGetUIButtonProperty(uiHandle, uiButtonID, &prop, operationMode));
            result.push_back(prop);
            return result;
        }

        simxInt simxSetUIButtonProperty (simxInt uiHandle, simxInt uiButtonID, simxInt prop, simxInt operationMode) {
            return ::simxSetUIButtonProperty(uiHandle, uiButtonID, prop, operationMode);
        }

        simxInt simxAddStatusbarMessage (const simxChar* message, simxInt operationMode) {
            return ::simxAddStatusbarMessage(message, operationMode);
        }

        UList simxAuxiliaryConsoleOpen (const simxChar* title, simxInt maxLines, simxInt mode, UList position, UList size,
                UList textColor, UList backgroundColor, simxInt operationMode) {
            int i, ret;

			simxInt* cc_size=NULL;
			simxInt* cc_pos=NULL;
			simxFloat* cc_textCol=NULL;
			simxFloat* cc_backCol=NULL;
            simxInt c_size[2];
            simxInt c_position[2];
            simxFloat c_textColor[3];
            simxFloat c_backgroundColor[3];

			if (position.size()>=2)
			{
	            for (i=0; i<2; i++) {
	             c_position[i] = position[i];
				}
				cc_pos=c_position;
			}

			if (size.size()>=2)
			{
	            for (i=0; i<2; i++) {
	             c_size[i] = size[i];
				}
				cc_size=c_size;
			}

			if (textColor.size()>=3)
			{
	            for (i=0; i<3; i++) {
	             c_textColor[i] = (ufloat)textColor[i];
				}
				cc_textCol=c_textColor;
			}

			if (backgroundColor.size()>=3)
			{
	            for (i=0; i<3; i++) {
	             c_backgroundColor[i] = (ufloat)backgroundColor[i];
				}
				cc_backCol=c_backgroundColor;
			}

			simxInt consoleHandle;

            UList result;

            result.push_back(::simxAuxiliaryConsoleOpen(title, maxLines, mode, cc_pos, cc_size, cc_textCol, cc_backCol, &consoleHandle, operationMode));
            result.push_back(consoleHandle);
            return result;
        }

        simxInt simxAuxiliaryConsoleClose (simxInt consoleHandle, simxInt operationMode) {
            return ::simxAuxiliaryConsoleClose(consoleHandle, operationMode);
        }

        simxInt simxAuxiliaryConsolePrint (simxInt consoleHandle, const simxChar* txt, simxInt operationMode) {
			simxChar* cc_txt=NULL;
			if (strlen(txt)!=0)
				cc_txt=(simxChar*)txt;
            return ::simxAuxiliaryConsolePrint(consoleHandle, cc_txt, operationMode);
        }

        simxInt simxAuxiliaryConsoleShow (simxInt consoleHandle, int showState, simxInt operationMode) {
            return ::simxAuxiliaryConsoleShow(consoleHandle, (simxChar) showState, operationMode);
        }

        UList simxGetObjectOrientation (simxInt objectHandle, simxInt relativeToObjectHandle, simxInt operationMode) {
            int ret, i;
            simxFloat c_eulerAngles[3];

            UList eulerAngles;
            UList result;

            ret = ::simxGetObjectOrientation(objectHandle, relativeToObjectHandle, c_eulerAngles, operationMode);
            if (ret == 0) {
                for (i=0; i<3; i++) {
                    eulerAngles.push_back(c_eulerAngles[i]);
                }
            }

            result.push_back(ret);
            result.push_back(eulerAngles);
            return result;
        }

        UList simxGetObjectPosition (simxInt objectHandle, simxInt relativeToObjectHandle, simxInt operationMode) {
            int ret, i;
            simxFloat c_position[3];

            UList position;
            UList result;

            ret = ::simxGetObjectPosition(objectHandle, relativeToObjectHandle, c_position, operationMode);
            if (ret == 0) {
                for (i=0; i<3; i++) {
                    position.push_back(c_position[i]);
                }
            }

            result.push_back(ret);
            result.push_back(position);
            return result;
        }

        simxInt simxSetObjectOrientation (simxInt objectHandle, simxInt relativeToObjectHandle, UList eulerAngles, simxInt operationMode) {
            int i;
            simxFloat c_eulerAngles[3];           
            for (i=0; i<3; i++) {
                c_eulerAngles[i] = (ufloat) eulerAngles[i];
            }
            return ::simxSetObjectOrientation(objectHandle, relativeToObjectHandle, c_eulerAngles, operationMode);
        }

        simxInt simxSetObjectPosition (simxInt objectHandle, simxInt relativeToObjectHandle, UList position, simxInt operationMode) {
            int i;
            simxFloat c_position[3];           
            for (i=0; i<3; i++) {
                c_position[i] = (ufloat) position[i];
            }

            return  ::simxSetObjectPosition(objectHandle, relativeToObjectHandle, c_position, operationMode);
        }

        simxInt simxSetObjectParent (simxInt objectHandle, simxInt parentObject, int keepInPlace, simxInt operationMode) {
            return ::simxSetObjectParent(objectHandle, parentObject, (simxChar) keepInPlace, operationMode);
        }

        simxInt simxSetUIButtonLabel (simxInt uiHandle, simxInt uiButtonID, const simxChar* upStateLabel, const simxChar* downStateLabel, simxInt operationMode) {
            return ::simxSetUIButtonLabel(uiHandle, uiButtonID, upStateLabel, downStateLabel, operationMode);
        }

        UList simxGetLastErrors (simxInt operationMode) {
            int ret, i;
            simxInt errorCnt;
            simxChar *c_errorStrings;

            UList errorStrings;
            UList result;

            ret = ::simxGetLastErrors(&errorCnt, &c_errorStrings, operationMode);
            if (ret == 0) {
                for (i=0; i<errorCnt; i++) {
                    std::string err_str(strdup(c_errorStrings));
                    errorStrings.push_back(err_str);
                    c_errorStrings += strlen(c_errorStrings) + 1; // one for NULL byte
                }
            }

            result.push_back(ret);
            result.push_back(errorStrings);
            return result;
        }

        UList simxGetArrayParameter (simxInt paramIdentifier, simxInt operationMode) {
            int i, ret;
            UList paramValues;
            UList result;            
            simxFloat c_paramValues[3];

            ret = ::simxGetArrayParameter(paramIdentifier, c_paramValues, operationMode);
            if (ret == 0) {
                for (i=0; i<3; i++) {
                    paramValues.push_back(c_paramValues[i]);
                }
            }

            result.push_back(ret);
            result.push_back(paramValues);
            return result;
        }

        simxInt simxSetArrayParameter (simxInt paramIdentifier, UList paramValues, simxInt operationMode) {
            int i;
            simxFloat c_paramValues[3];

            for (i=0; i<3; i++) {
                c_paramValues[i] = (ufloat) paramValues[i];
            }
            return ::simxSetArrayParameter(paramIdentifier, c_paramValues, operationMode);
        }

        UList simxGetBooleanParameter (simxInt paramIdentifier, simxInt operationMode) {
            UList result;
            simxChar paramValue;
            result.push_back(::simxGetBooleanParameter(paramIdentifier, &paramValue, operationMode));
            result.push_back((int) paramValue);
            return result;
        }

        simxInt simxSetBooleanParameter (simxInt paramIdentifier, simxInt paramValue, simxInt operationMode) {
            return ::simxSetBooleanParameter(paramIdentifier, (simxChar) paramValue, operationMode);
        }

        UList simxGetIntegerParameter (simxInt paramIdentifier, simxInt operationMode) {
            UList result;
            simxInt paramValue;
            result.push_back(::simxGetIntegerParameter(paramIdentifier, &paramValue, operationMode));
            result.push_back(paramValue);
            return result;
        }

        simxInt simxSetIntegerParameter (simxInt paramIdentifier, simxInt paramValue, simxInt operationMode) {
            return ::simxSetIntegerParameter(paramIdentifier, paramValue, operationMode);
        }

        UList simxGetFloatingParameter (simxInt paramIdentifier, simxInt operationMode) {
            UList result;
            simxFloat paramValue;
            result.push_back(::simxGetFloatingParameter(paramIdentifier, &paramValue, operationMode));
            result.push_back(paramValue);
            return result;
        }

        simxInt simxSetFloatingParameter (simxInt paramIdentifier, ufloat paramValue, simxInt operationMode) {
            return ::simxSetFloatingParameter(paramIdentifier, (float) paramValue, operationMode);
        }

        UList simxGetStringParameter (simxInt paramIdentifier, simxInt operationMode) {
            UList result;
			int ret;
            simxChar *paramValue;
			ret=::simxGetStringParameter(paramIdentifier, &paramValue, operationMode);
            result.push_back(ret);
			if (ret==0)
	            result.push_back(paramValue);
			else
	            result.push_back("");
            return result;
        }

        UList simxGetCollisionHandle (const simxChar* collisionObjectName, simxInt operationMode) {
            UList result;
            simxInt handle;
            result.push_back(::simxGetCollisionHandle(collisionObjectName, &handle, operationMode));
            result.push_back(handle);
            return result;
        }

        UList simxGetDistanceHandle (const simxChar* distanceObjectName, simxInt operationMode) {
            UList result;
            simxInt handle;
            result.push_back(::simxGetDistanceHandle(distanceObjectName, &handle, operationMode));
            result.push_back(handle);
            return result;
        }

        UList simxReadCollision (simxInt collisionObjectHandle, simxInt operationMode) {
            UList result;
            simxChar collisionState;
            result.push_back(::simxReadCollision(collisionObjectHandle, &collisionState, operationMode));
            result.push_back(collisionState);
            return result;
        }

        UList simxReadDistance (simxInt distanceObjectHandle, simxInt operationMode) {
            UList result;
            simxFloat minimumDistance;
            result.push_back(::simxReadDistance(distanceObjectHandle, &minimumDistance, operationMode));
            result.push_back(minimumDistance);
            return result;
        }

        simxInt simxRemoveObject (simxInt objectHandle, simxInt operationMode) {
            return ::simxRemoveObject(objectHandle, operationMode);
        }

        simxInt simxRemoveUI (simxInt uiHandle, simxInt operationMode) {
            return ::simxRemoveUI(uiHandle, operationMode);
        }

        simxInt simxCloseScene (simxInt operationMode) {
            return ::simxCloseScene(operationMode);
        }

        UList simxGetObjects (simxInt objectType, simxInt operationMode) {
            UList result;
            UList objectHandles;

            int ret, i;
            simxInt objectCount;
            simxInt *c_objectHandles;
            
            ret = ::simxGetObjects(objectType, &objectCount, &c_objectHandles, operationMode);
            if (ret == 0) {
                for (i=0; i<objectCount; i++) {
                    objectHandles.push_back(c_objectHandles[i]);
                }
            }

            result.push_back(ret);
            result.push_back(objectHandles);
            return result;
        }

        UList simxDisplayDialog (const simxChar* titleText, const simxChar* mainText, simxInt dialogType, 
                const simxChar* initialText, UList tileColors, UList dialogColors, simxInt operationMode) {
            int ret,i;
            simxInt uiHandle;
            simxInt dialogHandle;
            simxFloat c_titleColors[6];
            simxFloat c_dialogColors[6];
            simxFloat* cc_titleColors=NULL;
            simxFloat* cc_dialogColors=NULL;

            UList result;

			if (tileColors.size()>=6)
			{
				for (i=0; i<6; i++)
					c_titleColors[i]=(ufloat)tileColors[i];
				cc_titleColors=c_titleColors;
			}

			if (dialogColors.size()>=6)
			{
				for (i=0; i<6; i++)
					c_dialogColors[i]=(ufloat)dialogColors[i];
				cc_dialogColors=c_dialogColors;
			}

            ret = ::simxDisplayDialog(titleText, mainText, dialogType, initialText, cc_titleColors, cc_dialogColors, &dialogHandle, &uiHandle, operationMode);
            result.push_back(ret);
            result.push_back(dialogHandle);
            result.push_back(uiHandle);
            return result;
        }

        simxInt simxEndDialog (simxInt dialogHandle, simxInt operationMode) {
            return ::simxEndDialog(dialogHandle, operationMode);
        }

        UList simxGetDialogInput (simxInt dialogHandle, simxInt operationMode) {
            UList result;
			int ret;
            simxChar *inputText;
			ret=::simxGetDialogInput(dialogHandle, &inputText, operationMode);
            result.push_back(ret);
			if (ret==0)
	            result.push_back(inputText);
			else
				result.push_back("");
            return result;
        }

        UList simxGetDialogResult (simxInt dialogHandle, simxInt operationMode) {
            UList result;
            simxInt c_result;
            result.push_back(::simxGetDialogResult(dialogHandle, &c_result, operationMode));
            result.push_back(c_result);
            return result;
        }

        UList simxCopyPasteObjects (UList objectHandles,simxInt operationMode) {
            int ret,i;
            simxInt newObjectCount;
            simxInt *c_newObjectHandles;
            simxInt *c_objectHandles;

            UList result;
            UList newObjectHandles;

            c_objectHandles = (simxInt*) malloc(sizeof(simxInt)*objectHandles.size());
            for (i=0; i<objectHandles.size(); i++) {
                c_objectHandles[i] = (simxInt)objectHandles[i];
            }

            ret = ::simxCopyPasteObjects(c_objectHandles, objectHandles.size(), &c_newObjectHandles, &newObjectCount, operationMode);
            if (ret == 0) {
                for (i=0; i<newObjectCount; i++) {
                    newObjectHandles.push_back(c_newObjectHandles[i]);
                }
            }
            result.push_back(ret);
            result.push_back(newObjectHandles);
            free(c_objectHandles);
            return result;
        }

        UList simxGetObjectSelection (simxInt operationMode) {
            int i, ret;
            simxInt objectCount;
            simxInt *c_objectHandles;
            
            UList objectHandles;
            UList result;

            ret = ::simxGetObjectSelection(&c_objectHandles, &objectCount, operationMode);
            if (ret == 0) {
                for (i=0; i<objectCount; i++) {
                    objectHandles.push_back(c_objectHandles[i]);                         
                }
            }

            result.push_back(ret);
            result.push_back(objectHandles);
            return result;
        }

        simxInt simxSetObjectSelection (UList objectHandles, simxInt operationMode) {
            int i,ret;
            simxInt *c_objectHandles;
            c_objectHandles = (simxInt*) malloc(sizeof(simxInt) * objectHandles.size());

            for (i=0; i<objectHandles.size(); i++) {
                c_objectHandles[i] = objectHandles[i];
            }

            ret = ::simxSetObjectSelection(c_objectHandles, objectHandles.size(), operationMode);
            free(c_objectHandles);
            return ret;
        }

        simxInt simxClearFloatSignal (const simxChar* signalName, simxInt operationMode) {
            return  ::simxClearFloatSignal(signalName, operationMode);
        }

        simxInt simxClearIntegerSignal (const simxChar* signalName, simxInt operationMode) {
            return ::simxClearIntegerSignal(signalName, operationMode);
        }

        simxInt simxClearStringSignal (const simxChar* signalName, simxInt operationMode) {
            return ::simxClearStringSignal(signalName, operationMode);
        }

        UList simxGetFloatSignal (const simxChar* signalName, simxInt operationMode) {
            UList result;
            simxFloat signalValue;

            result.push_back(::simxGetFloatSignal(signalName, &signalValue, operationMode));
            result.push_back(signalValue);
            return result;
        }

        UList simxGetIntegerSignal (const simxChar* signalName, simxInt operationMode) {
            UList result;
            simxInt signalValue;

            result.push_back(::simxGetIntegerSignal(signalName, &signalValue, operationMode));
            result.push_back(signalValue);
            return result;
        }

        UList simxGetStringSignal (const simxChar* signalName, simxInt operationMode) {
            UList result;
			int ret;
            simxChar *signalValue;
            simxInt signalLength;
			ret=::simxGetStringSignal(signalName, &signalValue, &signalLength, operationMode);
            result.push_back(ret);
			if (ret==0)
			{
				std::string s(signalValue,signalLength);
				UValue val(s);
				result.push_back(val);
			}
			else
	            result.push_back("");
            return result;
        }

        simxInt simxSetFloatSignal (const simxChar* signalName, ufloat signalValue, simxInt operationMode) {
            return ::simxSetFloatSignal(signalName, signalValue, operationMode);
        }

        simxInt simxSetIntegerSignal (const simxChar* signalName, simxInt signalValue, simxInt operationMode) {
            return ::simxSetIntegerSignal(signalName, signalValue, operationMode);
        }

        simxInt simxSetStringSignal (const simxChar* signalName, UValue signalValue, simxInt operationMode) {
			simxInt ret=simx_error_local_error_flag;
			if (signalValue.type==DATA_STRING)
			{
				ret=::simxSetStringSignal(signalName, signalValue.stringValue->c_str(), signalValue.stringValue->length(), operationMode);
			}
			return ret;
        }

        UList simxGetObjectFloatParameter (simxInt objectHandle, simxInt parameterID, simxInt operationMode) {
            UList result;
            simxFloat parameterValue;
            result.push_back(::simxGetObjectFloatParameter(objectHandle, parameterID, &parameterValue, operationMode));
            result.push_back(parameterValue);
            return result;
        }

        simxInt simxSetObjectFloatParameter (simxInt objectHandle, simxInt parameterID, ufloat parameterValue, simxInt operationMode) {
            return ::simxSetObjectFloatParameter(objectHandle, parameterID, parameterValue, operationMode);
        }

        UList simxGetObjectIntParameter (simxInt objectHandle, simxInt parameterID, simxInt operationMode) {
            UList result;
            simxInt parameterValue;
            result.push_back(::simxGetObjectIntParameter(objectHandle, parameterID, &parameterValue, operationMode));
            result.push_back(parameterValue);
            return result;
        }

        simxInt simxSetObjectIntParameter (simxInt objectHandle, simxInt parameterID, simxInt parameterValue, simxInt operationMode) {
            return ::simxSetObjectIntParameter(objectHandle, parameterID, parameterValue, operationMode);
        }

        UList simxGetModelProperty (simxInt objectHandle, simxInt operationMode) {
            UList result;
            simxInt prop;
            result.push_back(::simxGetModelProperty(objectHandle, &prop, operationMode));
            result.push_back(prop);
            return result;
        }

        simxInt simxSetModelProperty (simxInt objectHandle, simxInt prop, simxInt operationMode) {
            return ::simxSetModelProperty(objectHandle, prop, operationMode);
        }

        simxInt simxStart (const simxChar* connectionAddress, simxInt connectionPort, int waitUntilConnected, int doNotReconnectOnceDisconnected,simxInt timeOutInMs) {
            return ::simxStart(connectionAddress, connectionPort, (simxChar) waitUntilConnected, (simxChar) doNotReconnectOnceDisconnected,timeOutInMs);
        }

        simxVoid simxFinish () {
            ::simxFinish();
        }

        UList simxGetPingTime () {
            UList result;
            simxInt pingTime;
            result.push_back(::simxGetPingTime(&pingTime));
            result.push_back(pingTime);
            return result;
        }

        simxInt simxGetLastCmdTime () {
            return ::simxGetLastCmdTime();
        }

        simxInt simxSynchronousTrigger () {
            return ::simxSynchronousTrigger();
        }

        simxInt simxSynchronous (int enable) {
            return ::simxSynchronous((simxChar) enable);
        }

        simxInt simxPauseCommunication (int enable) {
            return ::simxPauseCommunication((simxChar) enable);
        }

        UList simxGetInMessageInfo (simxInt infoType) {
            UList result;
            simxInt info;
            result.push_back(::simxGetInMessageInfo(infoType, &info));
            result.push_back(info);
            return result;
        }

        UList simxGetOutMessageInfo (simxInt infoType) {
            UList result;
            simxInt info;
            result.push_back(::simxGetOutMessageInfo(infoType, &info));
            result.push_back(info);
            return result;
        }

        simxInt simxGetConnectionId () {
            return ::simxGetConnectionId();
        }

        simxInt simxTransferFile (const simxChar* filePathAndName, const simxChar* fileName_serverSide, simxInt timeOut, simxInt operationMode) {
            return ::simxTransferFile(filePathAndName, fileName_serverSide, timeOut, operationMode);
        }

        simxInt simxEraseFile (const simxChar* fileName_serverSide, simxInt operationMode) {
            return ::simxEraseFile(fileName_serverSide, operationMode);
        }

};

// Register the class to the Urbi kernel. 
UStart (vrep);


