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

class remoteApi
{
	static{	
		System.loadLibrary("remoteApiJava");
	}
	native int test(StringWA errorStrings,StringW test, int operationMode);

	native int simxStart(final String connectionAddress, int connectionPort, boolean waitUntilConnected, boolean doNotReconnectOnceDisconnected, int timeOutInMs);
	native void simxFinish();
	native int simxGetConnectionId();
	native int simxGetObjectHandle(final String objectName, IntW handle, int operationMode);
	native int simxGetJointPosition(int jointHandle, FloatW position, int operationMode);
	native int simxSetJointPosition(int jointHandle, float position, int operationMode);
	native int simxGetObjectPosition(int objectHandle, int relativeToObjectHandle, FloatWA position, int operationMode);
	native int simxSetObjectPosition(int objectHandle, int relativeToObjectHandle, final FloatWA position, int operationMode);
	native int simxGetVisionSensorImage(int sensorHandle, IntWA resolution, CharWA image, int options, int operationMode);
	native int simxSetVisionSensorImage(int sensorHandle, CharWA image, int bufferSize, int options, int operationMode);
	native int simxGetJointMatrix(int jointHandle, FloatWA matrix, int operationMode);
	native int simxSetSphericalJointMatrix(int jointHandle,FloatWA matrix,int operationMode);
	native int simxSetJointTargetVelocity(int jointHandle,float targetVelocity,int operationMode);
	native int simxSetJointTargetPosition(int jointHandle,float targetPosition,int operationMode);
	native int simxJointGetForce(int jointHandle,FloatW force,int operationMode);
	native int simxSetJointForce(int jointHandle,float force,int operationMode);
	native int simxReadForceSensor(int forceSensorHandle, IntW state,FloatWA forceVector,FloatWA torqueVector,int operationMode);
	native int simxBreakForceSensor(int forceSensorHandle,int operationMode);
	native int simxReadVisionSensor(int sensorHandle,BoolW detectionState, FloatWAA auxValues, int operationMode);
	native int simxGetObjectFloatParameter(int objectHandle,int parameterID,FloatW parameterValue,int operationMode);
	native int simxSetObjectFloatParameter(int objectHandle,int parameterID,float parameterValue,int operationMode);
	native int simxGetObjectIntParameter(int objectHandle,int parameterID,IntW parameterValue,int operationMode);
	native int simxSetObjectIntParameter(int objectHandle,int parameterID,int parameterValue,int operationMode);
	native int simxGetModelProperty(int objectHandle,IntW prop,int operationMode);
	native int simxSetModelProperty(int objectHandle,int prop,int operationMode);
	native int simxGetVisionSensorDepthBuffer(int sensorHandle,IntWA resolution,FloatWA buffer,int operationMode);
	native int simxGetObjectChild(int parentObjectHandle,int childIndex,IntW childObjectHandle,int operationMode);
	native int simxGetObjectParent(int childObjectHandle,IntW parentObjectHandle,int operationMode);
	native int simxStartSimulation(int operationMode);
	native int simxPauseSimulation(int operationMode);
	native int simxStopSimulation(int operationMode);
	native int simxGetUISlider(int uiHandle,int uiButtonID,IntW position,int operationMode);
	native int simxSetUISlider(int uiHandle,int uiButtonID,int position,int operationMode);
	native int simxGetUIEventButton(int uiHandle,IntW uiEventButtonID,IntWA auxValues,int operationMode);
	native int simxGetUIButtonProperty(int uiHandle,int uiButtonID,IntW prop,int operationMode);
	native int simxSetUIButtonProperty(int uiHandle,int uiButtonID,int prop,int operationMode);
	native int simxAuxiliaryConsoleClose(int consoleHandle,int operationMode);
	native int simxAuxiliaryConsoleShow(int consoleHandle,boolean showState,int operationMode);
	native int simxGetObjectOrientation(int objectHandle,int relativeToObjectHandle,FloatWA eulerAngles,int operationMode);
	native int simxSetObjectParent(int objectHandle,int parentObject,boolean keepInPlace,int operationMode);
	native int simxGetArrayParameter(int paramIdentifier,FloatWA paramValues,int operationMode);
	native int simxSetArrayParameter(int paramIdentifier,FloatWA paramValues,int operationMode);
	native int simxGetIntegerParameter(int paramIdentifier,IntW paramValue,int operationMode);
	native int simxSetIntegerParameter(int paramIdentifier,int paramValue,int operationMode);
	native int simxGetBooleanParameter(int paramIdentifier,BoolW paramValue,int operationMode);
	native int simxGetDialogResult(int dialogHandle,IntW result,int operationMode);
	native int simxSetFloatingParameter(int paramIdentifier,float paramValue,int operationMode);
	native int simxRemoveObject(int objectHandle,int operationMode);
	native int simxRemoveUI(int uiHandle,int operationMode);
	native int simxCloseScene(int operationMode);
	native int simxEndDialog(int dialogHandle,int operationMode);
	native int simxReadDistance(int distanceObjectHandle,FloatW minimumDistance,int operationMode);
	native int simxGetFloatingParameter(int paramIdentifier,FloatW paramValue,int operationMode);
	native int simxSetObjectOrientation(int objectHandle,int relativeToObjectHandle,FloatWA eulerAngles,int operationMode);
	native int simxReadProximitySensor(int sensorHandle, BoolW detectionState, FloatWA detectedPoint, IntW detectedObjectHandle, FloatWA detectedSurfaceNormalVector,int operationMode);

	native int simxLoadModel(final String modelPathAndName, int options, IntW baseHandle, int operationMode);
	native int simxLoadUI(final String uiPathAndName, int options, IntWA uiHandles, int operationMode);
	native int simxLoadScene(final String scenePathAndName, int options, int operationMode);
	native int simxGetUIHandle(final String uiName,IntW handle,int operationMode);
	native int simxAddStatusbarMessage(final String message,int operationMode);
	native int simxAuxiliaryConsoleOpen(final String title,int maxLines,int mode,IntWA position,IntWA size,FloatWA textColor,FloatWA backgroundColor,IntW consoleHandle,int operationMode);
	native int simxAuxiliaryConsolePrint(int consoleHandle, final String txt,int operationMode);
	native int simxSetUIButtonLabel(int uiHandle,int uiButtonID,final String upStateLabel,final String downStateLabel,int operationMode);
	native int simxGetLastErrors(StringWA errorStrings,int operationMode);
	native int simxSetBooleanParameter(int paramIdentifier,boolean paramValue,int operationMode);
	native int simxGetStringParameter(int paramIdentifier,StringW paramValue,int operationMode);
	native int simxGetCollisionHandle(final String collisionObjectName,IntW handle,int operationMode);
	native int simxGetDistanceHandle(final String distanceObjectName,IntW handle,int operationMode);
	native int simxReadCollision(int collisionObjectHandle,BoolW collisionState,int operationMode);
	native int simxGetObjects(int objectType,IntWA objectHandles,int operationMode);
	native int simxDisplayDialog(final String titleText,final String mainText,int dialogType,final String initialText,FloatWA titleColors,FloatWA dialogColors,IntW dialogHandle,IntW uiHandle,int operationMode);
	native int simxGetDialogInput(int dialogHandle,StringW inputText,int operationMode);
	native int simxCopyPasteObjects(IntWA objectHandles, IntWA newObjectHandles, int operationMode);
	native int simxGetObjectSelection(IntWA objectHandles, int operationMode);
	native int simxSetObjectSelection(IntWA objectHandles, int operationMode);
	native int simxClearFloatSignal(final String signalName, int operationMode);
	native int simxClearStringSignal(final String signalName,int operationMode);
	native int simxClearIntegerSignal(final String signalName,int operationMode);
	native int simxGetFloatSignal(final String signalName,FloatW signalValue,int operationMode);
	native int simxGetIntegerSignal(final String signalName,IntW signalValue,int operationMode);
	native int simxGetStringSignal(final String signalName, StringW signalValue, int operationMode);

	native int simxSetFloatSignal(final String signalName,float signalValue,int operationMode);
	native int simxSetIntegerSignal(final String signalName,int signalValue,int operationMode);
	native int simxSetStringSignal(final String signalName, final String signalValue, int operationMode);

	native int simxGetPingTime(IntW pingTime);
	native int simxGetLastCmdTime();
	native int simxSynchronousTrigger();
	native int simxSynchronous(boolean enable);
	native int simxPauseCommunication(boolean enable);
	native int simxGetInMessageInfo(int infoType, IntW info);
	native int simxGetOutMessageInfo(int infoType, IntW info);
	native int simxTransferFile(final String filePathAndName, final String fileName_serverSide, int timeOut, int operationMode);
	native int simxEraseFile(final String fileName_serverSide, int operationMode);

	public static final int SIMX_HEADER_SIZE = 18;
	public static final int simx_headeroffset_crc = 0;				/* 1 simxUShort. Generated by the client or server. The CRC for the message */
	public static final int simx_headeroffset_version = 2;			/* 1 byte. Generated by the client or server. The version of the remote API software */
	public static final int simx_headeroffset_message_id = 3;		/* 1 simxInt. Generated by the client (and used in a reply by the server) */
	public static final int simx_headeroffset_client_time = 7;		/* 1 simxInt. Client time stamp generated by the client (and sent back by the server) */
	public static final int simx_headeroffset_server_time = 11;	/* 1 simxInt. Generated by the server when a reply is generated. The server timestamp */
	public static final int simx_headeroffset_scene_id = 15;		/* 1 simxUShort. Generated by the server. A unique ID identifying the scene currently displayed */
	public static final int simx_headeroffset_server_state = 17;	/* 1 byte. Generated by the server. Bit coded: 0 set --> simulation not stopped, 1 set --> simulation paused, 2 set --> real-time switch on, 3-5: edit mode type (0=no edit mode, 1=triangle, 2=vertex, 3=edge, 4=path, 5=UI) */ 

	/* Remote API command header: */
	public static final int SIMX_SUBHEADER_SIZE = 26;
	public static final int simx_cmdheaderoffset_mem_size = 0;			/* 1 simxInt. Generated by the client or server. The buffer size of the command. */
	public static final int simx_cmdheaderoffset_full_mem_size = 4;	/* 1 simxInt. Generated by the client or server. The full buffer size of the command (applies to split chunks). */
	public static final int simx_cmdheaderoffset_pdata_offset0 = 8;	/* 1 simxUShort. Generated by the client or server. The amount of data that is part of the command identification. */
	public static final int simx_cmdheaderoffset_pdata_offset1 = 10;	/* 1 simxInt. Generated by the client or server. The amount of shift of the pure data buffer (applies to split chunks). */
	public static final int simx_cmdheaderoffset_cmd = 14;				/* 1 simxInt. Generated by the client (and used in a reply by the server). The command, combined with the operation mode of the command. */
	public static final int simx_cmdheaderoffset_delay_or_split = 18;	/* 1 simxUShort. Generated by the client or server. The amount of delay in ms of a continuous command, or the max. pure data size to send at once (applies to split commands). */
	public static final int simx_cmdheaderoffset_sim_time = 20;		/* 1 simxInt. Generated by the server. The simulation time (in ms) when the command was executed (or 0 if simulation is not running) */
	public static final int simx_cmdheaderoffset_status = 24;			/* 1 byte. Generated by the server. (1: bit 0 is set --> error in function execution on server side). The client writes bit 1 if command cannot be overwritten*/
	public static final int simx_cmdheaderoffset_reserved = 25;		/* 1 byte. Not yet used */


	public static final int sim_object_shape_type 					= 0;
	public static final int sim_object_joint_type 						= 1;
	public static final int sim_object_graph_type 					= 2;
	public static final int sim_object_camera_type 					= 3;
	public static final int sim_object_dummy_type 					= 4;
	public static final int sim_object_proximitysensor_type 			= 5;
	public static final int sim_object_reserved1 						= 6;
	public static final int sim_object_reserved2 						= 7;
	public static final int sim_object_path_type 						= 8;
	public static final int sim_object_visionsensor_type 				= 9;
	public static final int sim_object_volume_type 					= 10; 
	public static final int sim_object_mill_type 						= 11;
	public static final int sim_object_forcesensor_type 				= 12;
	public static final int sim_object_light_type 						= 13;
	public static final int sim_object_mirror_type 						= 14;
	public static final int sim_object_type_end 						= 108;

	public static final int  sim_appobj_object_type  					= 109;
	public static final int sim_appobj_collision_type 					= 110;
	public static final int sim_appobj_distance_type 					= 111;
	public static final int sim_appobj_simulation_type 				= 112;
	public static final int sim_appobj_ik_type 						= 113;
	public static final int sim_appobj_constraintsolver_type			= 114;
	public static final int sim_appobj_collection_type 				= 115;
	public static final int sim_appobj_ui_type 						= 116;
	public static final int sim_appobj_script_type 					= 117;
	public static final int sim_appobj_pathplanning_type 			= 118;
	public static final int sim_appobj_RESERVED_type 				= 119;
	public static final int sim_appobj_texture_type 					= 120;

	public static final int sim_ik_pseudo_inverse_method 			= 0;
	public static final int sim_ik_damped_least_squares_method 	= 1;
	public static final int sim_ik_jacobian_transpose_method		= 2;

	public static final int sim_ik_x_constraint 						= 1;
	public static final int sim_ik_y_constraint 						= 2;
	public static final int sim_ik_z_constraint 						= 4;
	public static final int sim_ik_alpha_beta_constraint 				= 8;
	public static final int sim_ik_gamma_constraint 					= 16;
	public static final int sim_ik_avoidance_constraint 				= 64;

	public static final int sim_ikresult_not_performed 				= 0;
	public static final int sim_ikresult_success 						= 1;
	public static final int sim_ikresult_fail 							= 2;

	/* Light sub-types: */
	public static final int sim_light_omnidirectional_subtype 		= 1;
	public static final int sim_light_spot_subtype 					= 2;
	public static final int sim_light_directional_subtype 				= 3;
	/* Joint sub-types: */
	public static final int sim_joint_revolute_subtype 				= 10;
	public static final int sim_joint_prismatic_subtype 				= 11;
	public static final int sim_joint_spherical_subtype 				= 12;
	/* Shape sub-types: */
	public static final int sim_shape_simpleshape_subtype 			= 20;
	public static final int sim_shape_multishape_subtype 			= 21;
	/* Proximity sensor sub-types: */
	public static final int sim_proximitysensor_pyramid_subtype 	= 30;
	public static final int sim_proximitysensor_cylinder_subtype 	= 31;
	public static final int sim_proximitysensor_disc_subtype 		= 32;
	public static final int sim_proximitysensor_cone_subtype 		= 33;
	public static final int sim_proximitysensor_ray_subtype 		= 34;
	/* Mill sub-types: */
	public static final int sim_mill_pyramid_subtype 				= 40;
	public static final int sim_mill_cylinder_subtype 					= 41;
	public static final int sim_mill_disc_subtype 						= 42;
	public static final int sim_mill_cone_subtype 					= 43;
	/* No sub-type: */
	public static final int sim_object_no_subtype 					= 200;

	/* Scene object main properties (serialized): */
	public static final int sim_objectspecialproperty_collidable 		= 0x0001;
	public static final int sim_objectspecialproperty_measurable 	= 0x0002;
	/*reserved						=0x0004, */
	/*reserved						=0x0008, */
	public static final int sim_objectspecialproperty_detectable_ultrasonic = 16;
	public static final int sim_objectspecialproperty_detectable_infrared = 32;
	public static final int sim_objectspecialproperty_detectable_laser = 64;
	public static final int sim_objectspecialproperty_detectable_inductive = 128;
	public static final int sim_objectspecialproperty_detectable_capacitive = 256;
	public static final int sim_objectspecialproperty_renderable = 512;
	public static final int sim_objectspecialproperty_detectable_all = 16 | 32 | 64 | 128 | 256;
	public static final int sim_objectspecialproperty_cuttable = 1024;
	public static final int sim_objectspecialproperty_pathplanning_ignored = 2048;

	public static final int sim_modelproperty_not_collidable = 1;
	public static final int sim_modelproperty_not_measurable = 2;
	public static final int sim_modelproperty_not_renderable = 4;
	public static final int sim_modelproperty_not_detectable = 8;
	public static final int sim_modelproperty_not_cuttable = 16;
	public static final int sim_modelproperty_not_dynamic = 32;
	public static final int sim_modelproperty_not_respondable = 64; /* cannot be selected if sim_modelproperty_not_dynamic is not selected */
	public static final int sim_modelproperty_not_reset = 128; /* Model is not reset at simulation end. This flag is cleared at simulation end */
	public static final int sim_modelproperty_not_visible = 256; /* Whole model is invisible, independent of local visibility settings */
	public static final int sim_modelproperty_not_model = 61440;  /* object is not a model */

		/* Check the documentation instead of comments below!! */
	/* Following messages are dispatched to the Lua-message container: */
	public static final int sim_message_ui_button_state_change = 0;	/* a UI button, slider, etc. changed (due to a user's action). aux[0]=UI handle, aux[1]=button handle, aux[2]=button attributes, aux[3]=slider position (if slider) */
	public static final int sim_message_reserved9 = 1;					/* Do not use */
	public static final int sim_message_object_selection_changed = 2;
	public static final int im_message_reserved10 = 3;					/* do not use */
	public static final int sim_message_model_loaded = 4;
	public static final int sim_message_reserved11 = 5;					/* do not use */
	public static final int sim_message_keypress = 6;					/* a key was pressed while the focus was on a page (aux[0]=key, aux[1]=ctrl and shift key state) */
	public static final int sim_message_bannerclicked = 7;				/* a banner was clicked (aux[0]=banner ID) */

	/* Following messages are dispatched only to the C-API (not available from Lua): */
	public static final int sim_message_for_c_api_only_start = 256;			/* Do not use */
	public static final int sim_message_reserved1 = 257;								/* Do not use */
	public static final int sim_message_reserved2 = 258;								/* Do not use */
	public static final int sim_message_reserved3 = 259;								/* Do not use */

	public static final int sim_message_eventcallback_scenesave = 260;				/* about to save a scene */
	public static final int sim_message_eventcallback_modelsave = 261;			/* about to save a model (current selection will be saved) */
	public static final int sim_message_eventcallback_moduleopen = 262;				/* called when simOpenModule in Lua is called */
	public static final int sim_message_eventcallback_modulehandle = 263;				/* called when simHandleModule in Lua is called with argument false */
	public static final int sim_message_eventcallback_moduleclose = 264;				/* called when simCloseModule in Lua is called */
	public static final int sim_message_reserved4 = 265;								/* Do not use */
	public static final int sim_message_reserved5 = 266;								/* Do not use */
	public static final int sim_message_reserved6 = 267;								/* Do not use */
	public static final int sim_message_reserved7 = 268;								/* Do not use */
	public static final int sim_message_eventcallback_instancepass = 269;				/* Called once every main application loop pass. auxiliaryData[0] contains event flags of events that happened since last time: */
															/* bit0 set: object(s) erased */
															/* bit1 set: object(s) created */
															/* bit2 set: model loaded */
															/* bit3 set: scene loaded */
															/* bit4 set: undo called */
															/* bit5 set: redo called */
															/* bit6 set: scene switched (similar to scene loaded, basically: scene content completely changed) */
															/* bit7 set: edit mode active. This is not an event flag, but a state flag */
															/* bit8 set: object(s) scaled */
															/* bit9 set: selection state changed. (different objects are selected now) */
															/* bit10 set: key pressed */
															/* bit11 set: simulation started */
															/* bit12 set: simulation ended */

	public static final int sim_message_eventcallback_broadcast = 270;
	public static final int sim_message_eventcallback_imagefilter_enumreset = 271;
	public static final int sim_message_eventcallback_imagefilter_enumerate = 272;
	public static final int sim_message_eventcallback_imagefilter_adjustparams = 273;
	public static final int sim_message_eventcallback_imagefilter_reserved = 274;
	public static final int sim_message_eventcallback_imagefilter_process = 275;

	public static final int sim_message_eventcallback_reserved1 = 276; /* do not use */
	public static final int sim_message_eventcallback_reserved2 = 277; /* do not use */
	public static final int sim_message_eventcallback_reserved3 = 278; /* do not use */
	public static final int sim_message_eventcallback_reserved4 = 279; /* do not use */

	public static final int sim_message_eventcallback_abouttoundo = 280;		/* the undo button was hit and a previous state is about to be restored */
	public static final int sim_message_eventcallback_undoperformed = 281;	/* the undo button was hit and a previous state restored */
	public static final int sim_message_eventcallback_abouttoredo = 282;		/* the redo button was hit and a future state is about to be restored  */
	public static final int sim_message_eventcallback_redoperformed = 283;	/* the redo button was hit and a future state restored  */
	public static final int sim_message_eventcallback_scripticondblclick = 284; /* scipt icon was double clicked.  (aux[0]=object handle associated with script, set replyData[0] to 1 if script should not be opened)  */
	public static final int sim_message_eventcallback_simulationabouttostart = 285;
	public static final int sim_message_eventcallback_simulationended = 286;

	public static final int sim_message_eventcallback_reserved5 = 287;			/* do not use */
	public static final int sim_message_eventcallback_keypress = 288;			/* a key was pressed while the focus was on a page (aux[0]=key, aux[1]=ctrl and shift key state) */
	public static final int sim_message_eventcallback_modulehandleinsensingpart = 289; /* called when simHandleModule in Lua is called with argument true */

	public static final int sim_message_eventcallback_renderingpass = 290; /* called just before the scene is rendered */
	public static final int sim_message_eventcallback_bannerclicked = 291; /* called when a banner was clicked (aux[0]=banner ID) */
	public static final int sim_message_eventcallback_menuitemselected = 292; /* auxiliaryData[0] indicates the handle of the item, auxiliaryData[1] indicates the state of the item */
	public static final int sim_message_eventcallback_refreshdialogs = 293; /* aux[0]=refresh degree (0=light, 1=medium, 2=full) */
	public static final int sim_message_eventcallback_sceneloaded = 294;
	public static final int sim_message_eventcallback_modelloaded = 295;
	public static final int sim_message_eventcallback_instanceswitch = 296;


	public static final int sim_message_eventcallback_guipass = 297;
	public static final int sim_message_eventcallback_mainscriptabouttobecalled = 298;

	public static final int sim_message_simulation_start_resume_request = 4096; 
	public static final int sim_message_simulation_pause_request = 4097;
	public static final int sim_message_simulation_stop_request = 4098;
		

	public static final int sim_objectproperty_reserved1 = 0;
	public static final int sim_objectproperty_reserved2 = 1;
	public static final int sim_objectproperty_reserved3 = 2;
	public static final int sim_objectproperty_reserved4 = 3;
	public static final int sim_objectproperty_reserved5 = 4; /* formely sim_objectproperty_visible */
	public static final int sim_objectproperty_reserved6 = 8; /* formely sim_objectproperty_wireframe */
	public static final int sim_objectproperty_collapsed = 16;
	public static final int sim_objectproperty_selectable = 32; 
	public static final int sim_objectproperty_reserved7 = 64;
	public static final int sim_objectproperty_selectmodelbaseinstead = 128;
	public static final int sim_objectproperty_dontshowasinsidemodel = 256;
	/* reserved									=0x0200 */
		

	/* type of arguments (input and output) for custom lua commands */
	public static final int sim_lua_arg_nil = 0;			
	public static final int sim_lua_arg_bool = 1;		
	public static final int sim_lua_arg_int = 2;
	public static final int sim_lua_arg_float = 3;
	public static final int sim_lua_arg_string = 4;
	public static final int sim_lua_arg_invalid = 5;
	public static final int sim_lua_arg_table = 8;
		

	/* custom user interface properties. Values are serialized. */
	public static final int sim_ui_property_visible = 1;
	public static final int sim_ui_property_visibleduringsimulationonly = 2;
	public static final int sim_ui_property_moveable = 4;
	public static final int sim_ui_property_relativetoleftborder = 8;
	public static final int sim_ui_property_relativetotopborder = 256;
	public static final int sim_ui_property_fixedwidthfont = 32;
	public static final int sim_ui_property_systemblock = 64;
	public static final int sim_ui_property_settocenter =128;
	public static final int sim_ui_property_rolledup = 256;
	public static final int sim_ui_property_selectassociatedobject = 512;
	public static final int sim_ui_property_visiblewhenobjectselected = 1024;
		

	/* button properties. Values are serialized. */
	public static final int sim_buttonproperty_button = 0;
	public static final int sim_buttonproperty_label = 1;
	public static final int sim_buttonproperty_slider = 2;
	public static final int sim_buttonproperty_editbox = 3;
	public static final int sim_buttonproperty_staydown = 8;
	public static final int sim_buttonproperty_enabled = 16;
	public static final int sim_buttonproperty_borderless = 32;
	public static final int sim_buttonproperty_horizontallycentered = 64;
	public static final int sim_buttonproperty_ignoremouse = 128;
	public static final int sim_buttonproperty_isdown = 256;
	public static final int sim_buttonproperty_transparent = 512 ;
	public static final int sim_buttonproperty_nobackgroundcolor = 1024; 
	public static final int sim_buttonproperty_rollupaction = 2048;
	public static final int sim_buttonproperty_closeaction = 4096;
	public static final int sim_buttonproperty_verticallycentered = 8192;
	public static final int sim_buttonproperty_downupevent = 16384;

	/* Simulation status */
	public static final int sim_simulation_stopped = 0;								/* Simulation is stopped */
	public static final int sim_simulation_paused = 8;								/* Simulation is paused */
	public static final int sim_simulation_advancing = 16;								/* Simulation is advancing */
	public static final int sim_simulation_advancing_firstafterstop =16 |0;		/* First simulation pass (1x) */
	public static final int sim_simulation_advancing_running = 16|1;		/* Normal simulation pass (>=1x) */
	/* reserved									=sim_simulation_advancing|0x02, */
	public static final int sim_simulation_advancing_lastbeforepause = 16|3;		/* Last simulation pass before pause (1x) */
	public static final int sim_simulation_advancing_firstafterpause = 16|4;		/* First simulation pass after pause (1x) */
	public static final int sim_simulation_advancing_abouttostop = 16|5;		/* "Trying to stop" simulation pass (>=1x) */
	public static final int sim_simulation_advancing_lastbeforestop = 16|6;		/* Last simulation pass (1x) */

	/* Script execution result (first return value) */
	public static final int sim_script_no_error = 0;
	public static final int sim_script_main_script_nonexistent = 1;
	public static final int sim_script_main_script_not_called = 2;
	public static final int sim_script_reentrance_error = 4;
	public static final int sim_script_lua_error = 8;
	public static final int sim_script_call_error = 16;

	/* Script types (serialized!) */
	public static final int sim_scripttype_mainscript = 0;
	public static final int sim_scripttype_childscript = 1;
	public static final int sim_scripttype_pluginscript = 2;
	public static final int sim_scripttype_threaded = 240;		/* Combine with one of above's type values */
		

	/* API call error messages */
	public static final int sim_api_errormessage_ignore = 0;	/* does not memorize nor output errors */
	public static final int sim_api_errormessage_report = 1;	/* memorizes errors (default for C-API calls) */
	public static final int sim_api_errormessage_output = 2;  /* memorizes and outputs errors (default for Lua-API calls) */

	/* special argument of some functions: */
	public static final int sim_handle_all = -2;
	public static final int sim_handle_all_except_explicit = -3;
	public static final int sim_handle_self = -4;
	public static final int sim_handle_main_script = -5;
	public static final int sim_handle_tree = -6;
	public static final int sim_handle_chain = -7;
	public static final int sim_handle_single = -8;
	public static final int sim_handle_default = -9;
	public static final int sim_handle_all_except_self = -10;
	public static final int sim_handle_parent = -11;

	/* distance calculation methods: (serialized) */
	public static final int sim_distcalcmethod_dl = 0;
	public static final int sim_distcalcmethod_dac = 1;
	public static final int sim_distcalcmethod_max_dl_dac = 2;
	public static final int sim_distcalcmethod_dl_and_dac = 3;
	public static final int sim_distcalcmethod_sqrt_dl2_and_dac2 =4;
	public static final int sim_distcalcmethod_dl_if_nonzero = 5;
	public static final int sim_distcalcmethod_dac_if_nonzero = 6;

	/* Generic dialog styles: */
	public static final int sim_dlgstyle_message = 0;
	public static final int	sim_dlgstyle_input = 1;
	public static final int sim_dlgstyle_ok = 2;
	public static final int sim_dlgstyle_ok_cancel = 3;
	public static final int sim_dlgstyle_yes_no = 4;
	public static final int sim_dlgstyle_dont_center = 32; /* can be combined with one of above values. Only with this flag can the position of the related UI be set just after dialog creation  */
		
	/* Generic dialog return values: */
	public static final int sim_dlgret_still_open = 0;
	public static final int sim_dlgret_ok = 1;
	public static final int sim_dlgret_cancel = 2;
	public static final int sim_dlgret_yes = 3;
	public static final int sim_dlgret_no = 4;

	/* Path properties: */
	public static final int sim_pathproperty_show_line = 1;
	public static final int sim_pathproperty_show_orientation = 2;
	public static final int sim_pathproperty_closed_path = 4;
	public static final int sim_pathproperty_automatic_orientation = 8;
	public static final int sim_pathproperty_invert_velocity = 16;
	public static final int sim_pathproperty_infinite_acceleration = 32;
	public static final int sim_pathproperty_flat_path = 64;
	public static final int sim_pathproperty_show_position = 128;
	public static final int sim_pathproperty_auto_velocity_profile_translation = 256;
	public static final int sim_pathproperty_auto_velocity_profile_rotation = 512;
	public static final int sim_pathproperty_endpoints_at_zero = 1024;
	public static final int sim_pathproperty_keep_x_up = 2048;

	/* drawing objects: */
	/* following are mutually exclusive: */
	public static final int sim_drawing_points = 0;			/* 3 values per point (point size in pixels) */
	public static final int sim_drawing_lines = 1;				/* 6 values per line (line size in pixels) */
	public static final int sim_drawing_triangles = 2;			/* 9 values per triangle */
	public static final int sim_drawing_trianglepoints = 3;		/* 6 values per point (3 for triangle position, 3 for triangle normal vector) (triangle size in meters) */
	public static final int sim_drawing_quadpoints = 4;			/* 6 values per point (3 for quad position, 3 for quad normal vector) (quad size in meters) */
	public static final int sim_drawing_discpoints = 5;			/* 6 values per point (3 for disc position, 3 for disc normal vector) (disc size in meters) */
	public static final int sim_drawing_cubepoints = 6;			/* 6 values per point (3 for cube position, 3 for cube normal vector) (cube size in meters) */
	public static final int sim_drawing_spherepoints = 7;			/* 3 values per point (sphere size in meters) */

	/* following can be or-combined: */
	public static final int sim_drawing_itemcolors = 32; /* +3 values per item (each item has its own ambient color (r,g,b values)). Mutually exclusive with sim_drawing_vertexcolors */
	public static final int sim_drawing_vertexcolors = 64; /* +3 values per vertex (each vertex has its own ambient color (r,g,b values). Only for sim_drawing_lines (+6) and for sim_drawing_triangles(+9)). Mutually exclusive with sim_drawing_itemcolors */
	public static final int sim_drawing_itemsizes = 128; /* +1 value per item (each item has its own size). Not for sim_drawing_triangles */
	public static final int sim_drawing_backfaceculling = 256; /* back faces are not displayed for all items */
	public static final int sim_drawing_wireframe = 512; /* all items displayed in wireframe */
	public static final int sim_drawing_painttag = 1024; /* all items are tagged as paint (for additinal processing at a later stage) */
	public static final int sim_drawing_followparentvisibility = 2048; /* if the object is associated with a scene object, then it follows that visibility, otherwise it is always visible */
	public static final int sim_drawing_cyclic = 4096; /* if the max item count was reached, then the first items are overwritten. */
	public static final int sim_drawing_50percenttransparency = 8492; /* the drawing object will be 50% transparent */
	public static final int sim_drawing_25percenttransparency = 16384; /* the drawing object will be 25% transparent */
	public static final int sim_drawing_12percenttransparency = 32768; /* the drawing object will be 12.5% transparent */
	public static final int sim_drawing_emissioncolor = 65536; /* When used in combination with sim_drawing_itemcolors or sim_drawing_vertexcolors, then the specified colors will be for the emissive component */
	public static final int sim_drawing_facingcamera = 131072; /* Only for trianglepoints, quadpoints, discpoints and cubepoints. If specified, the normal verctor is calculated to face the camera (each item data requires 3 values less) */
	public static final int sim_drawing_overlay = 262144; /* When specified, objects are always drawn on top of "regular objects" */
	public static final int sim_drawing_itemtransparency= 524288;  /* +1 value per item (each item has its own transparency value (0-1)). Not compatible with sim_drawing_vertexcolors */
		
	/* banner values: */
	/* following can be or-combined: */
	public static final int sim_banner_left	= 1; /* Banners display on the left of the specified point */
	public static final int sim_banner_right= 2; /* Banners display on the right of the specified point */
	public static final int sim_banner_nobackground = 4; /* Banners have no background rectangle */
	public static final int sim_banner_overlay = 8; /* When specified, banners are always drawn on top of "regular objects" */
	public static final int sim_banner_followparentvisibility = 16; /* if the object is associated with a scene object, then it follows that visibility, otherwise it is always visible */
	public static final int sim_banner_clickselectsparent = 32; /* if the object is associated with a scene object, then clicking the banner will select the scene object */
	public static final int sim_banner_clicktriggersevent = 64; /* if the banner is clicked, an event is triggered (sim_message_eventcallback_bannerclicked and sim_message_bannerclicked are generated) */
	public static final int sim_banner_facingcamera = 128; /* If specified, the banner will always face the camera by rotating around the banner's vertical axis (y-axis) */
	public static final int sim_banner_fullyfacingcamera = 256; /* If specified, the banner will always fully face the camera (the banner's orientation is same as the camera looking at it) */
	public static final int sim_banner_backfaceculling = 512; /* If specified, the banner will only be visible from one side */
	public static final int sim_banner_keepsamesize = 1024; /* If specified, the banner will always appear in the same size. In that case size represents the character height in pixels */
	public static final int sim_banner_bitmapfont = 2048; /* If specified, a fixed-size bitmap font is used. The text will also always fully face the camera and be right to the specified position. Bitmap fonts are not clickable */
	
	/* particle objects: */
	/* following are mutually exclusive: */
	public static final int sim_particle_points1 = 0;			/* 6 values per point (pt1 and pt2. Pt1 is start position, pt2-pt1 is the initial velocity vector). Point is 1 pixel big. Only appearance is a point, internally handled as a perfect sphere */
	public static final int sim_particle_points2 = 1;			/* 6 values per point. Point is 2 pixel big. Only appearance is a point, internally handled as a perfect sphere */
	public static final int sim_particle_points4 = 2;			/* 6 values per point. Point is 4 pixel big. Only appearance is a point, internally handled as a perfect sphere */
	public static final int sim_particle_roughspheres = 3;		/* 6 values per sphere. Only appearance is rough. Internally a perfect sphere */
	public static final int sim_particle_spheres =4;			/* 6 values per sphere. Internally a perfect sphere */

	/* following can be or-combined: */
	public static final int sim_particle_respondable1to4 = 32; /* the particles are respondable against shapes (against all objects that have at least one bit 1-4 activated in the global respondable mask) */
	public static final int sim_particle_respondable5to8 = 64; /* the particles are respondable against shapes (against all objects that have at least one bit 5-8 activated in the global respondable mask) */
	public static final int sim_particle_particlerespondable = 128; /* the particles are respondable against each other */
	public static final int sim_particle_ignoresgravity = 256; /* the particles ignore the effect of gravity. Not compatible with sim_particle_water */
	public static final int sim_particle_invisible = 512; /* the particles are invisible */
	public static final int sim_particle_itemsizes = 1024; /* +1 value per particle (each particle can have a different size) */
	public static final int sim_particle_itemdensities = 2048; /* +1 value per particle (each particle can have a different density) */
	public static final int sim_particle_itemcolors = 4096; /* +3 values per particle (each particle can have a different color) */
	public static final int sim_particle_cyclic = 8192; /* if the max item count was reached, then the first items are overwritten. */
	public static final int sim_particle_emissioncolor = 16384; /* When used in combination with sim_particle_itemcolors, then the specified colors will be for the emissive component */
	public static final int sim_particle_water = 32768; /* the particles are water particles (no weight in the water (i.e. when z<0)). Not compatible with sim_particle_ignoresgravity */
	public static final int sim_particle_painttag = 65536; /* The particles can be seen by vision sensors (sim_particle_invisible must not be set) */
		

	/* custom user interface menu attributes: */
	public static final int sim_ui_menu_title = 1;
	public static final int sim_ui_menu_minimize = 2;
	public static final int sim_ui_menu_close = 4;
	public static final int sim_ui_menu_systemblock = 8;
		
	/* Boolean parameters: */
	public static final int	sim_boolparam_hierarchy_visible = 0;
	public static final int	sim_boolparam_console_visible = 1;
	public static final int	sim_boolparam_collision_handling_enabled = 2;
	public static final int	sim_boolparam_distance_handling_enabled = 3;
	public static final int	sim_boolparam_ik_handling_enabled = 4;
	public static final int	sim_boolparam_gcs_handling_enabled = 5;
	public static final int	sim_boolparam_dynamics_handling_enabled = 6;
	public static final int	sim_boolparam_joint_motion_handling_enabled = 7;
	public static final int	sim_boolparam_path_motion_handling_enabled = 8;
	public static final int	sim_boolparam_proximity_sensor_handling_enabled = 9;
	public static final int	sim_boolparam_vision_sensor_handling_enabled = 10;
	public static final int	sim_boolparam_mill_handling_enabled = 11;
	public static final int	sim_boolparam_browser_visible = 12;
	public static final int	sim_boolparam_scene_and_model_load_messages = 13;
	public static final int	sim_reserved0 = 14;
	public static final int	sim_boolparam_shape_textures_are_visible = 15;
	public static final int	sim_boolparam_display_enabled = 16;
	public static final int	sim_boolparam_infotext_visible = 17;
	public static final int	sim_boolparam_statustext_open = 18;
	public static final int	sim_boolparam_fog_enabled = 19;
	public static final int	sim_boolparam_rml2_available = 20;
	public static final int	sim_boolparam_rml4_available = 21;
	public static final int	sim_boolparam_mirrors_enabled = 22;
	public static final int	sim_boolparam_aux_clip_planes_enabled = 23;
	public static final int	sim_boolparam_full_model_copy_from_api = 24;
	public static final int	sim_boolparam_realtime_simulation = 25;
	


	/* Integer parameters: */
	public static final int sim_intparam_error_report_mode = 0; /* Check sim_api_errormessage_... constants above for valid values */
	public static final int sim_intparam_program_version = 1;		/* e.g Version 2.1.4 --> 20104. Can only be read */
	public static final int sim_intparam_instance_count =2;	/* do not use anymore (always returns 1 since V-REP 2.5.11) */
	public static final int sim_intparam_custom_cmd_start_id = 3; /* can only be read */
	public static final int sim_intparam_compilation_version = 4; /* 0=evaluation version, 1=full version, 2=player version. Can only be read */
	public static final int sim_intparam_current_page = 5;
 	public static final int sim_intparam_flymode_camera_handle = 6; /* can only be read */
	public static final int sim_intparam_dynamic_step_divider = 7; /* can only be read */
    public static final int	sim_intparam_dynamic_engine = 8; /* 0=Bullet, 1=ODE. Can only be read */
	public static final int	sim_intparam_server_port_start = 9;  /* can only be read */
	public static final int	sim_intparam_server_port_range = 10; /* can only be read */
	public static final int	sim_intparam_visible_layers = 11;
	public static final int	sim_intparam_infotext_style = 12;
	public static final int	sim_intparam_settings = 13;
	public static final int	sim_intparam_edit_mode_type = 14; /* can only be read */
	public static final int	sim_intparam_server_port_next =15; /* is initialized at sim_intparam_server_port_start */
	public static final int	sim_intparam_qt_version = 16; /* version of the used Qt framework */
	public static final int	sim_intparam_event_flags_read = 17; /* can only be read */
	public static final int	sim_intparam_event_flags_read_clear = 18; /* can only be read */
	public static final int	sim_intparam_platform = 19; /* can only be read */
	public static final int	sim_intparam_scene_unique_id = 20; /* can only be read */

	/* Float parameters: */
	public static final int sim_floatparam_rand = 0; /* random value (0.0-1.0) */
	public static final int sim_floatparam_simulation_time_step = 1; 
		
	/* String parameters: */
	public static final int	sim_stringparam_application_path = 0; /* path of V-REP's executable */
		
	/* Array parameters: */
	public static final int sim_arrayparam_gravity = 0;
	public static final int sim_arrayparam_fog = 1;
	public static final int sim_arrayparam_fog_color = 2;
	public static final int sim_arrayparam_background_color1 = 3;
	public static final int sim_arrayparam_background_color2 = 4;
	public static final int sim_arrayparam_ambient_light = 5; 

	/* User interface elements: */
	public static final int sim_gui_menubar = 1;
	public static final int sim_gui_popups = 2;
	public static final int sim_gui_toolbar1 = 4;
	public static final int sim_gui_toolbar2 = 8;
	public static final int sim_gui_hierarchy = 16;
	public static final int sim_gui_infobar = 32;
	public static final int sim_gui_statusbar = 64;
	public static final int sim_gui_scripteditor = 128;
	public static final int sim_gui_scriptsimulationparameters = 256;
	public static final int sim_gui_dialogs = 512;
	public static final int sim_gui_browser = 1024;
	public static final int	sim_gui_all = 65535;
		
	/* Joint modes: */
	public static final int	sim_jointmode_passive = 0;
	public static final int	sim_jointmode_motion = 1;
	public static final int	sim_jointmode_ik = 2;
	public static final int	sim_jointmode_ikdependent = 3;
	public static final int	sim_jointmode_dependent = 4;
	public static final int	sim_jointmode_force = 5;
		

	/* Navigation and selection modes with the mouse. Lower byte values are mutually exclusive, upper byte bits can be combined */
	public static final int sim_navigation_passive = 0;
	public static final int sim_navigation_camerashift = 1;
	public static final int sim_navigation_camerarotate = 2;
	public static final int sim_navigation_camerazoom = 3;
	public static final int sim_navigation_cameratilt = 4;
	public static final int sim_navigation_cameraangle = 5;
	public static final int sim_navigation_camerafly = 6;
	public static final int sim_navigation_objectshift = 7;
	public static final int sim_navigation_objectrotate = 8;
	public static final int sim_navigation_reserved2 = 9;
	public static final int sim_navigation_reserved3 = 10;
	public static final int sim_navigation_jointpathtest = 11;
	public static final int sim_navigation_ikmanip = 12;
	public static final int sim_navigation_objectmultipleselection = 13;
	/* Bit-combine following values and add them to one of above's values for a valid navigation mode: */
	public static final int sim_navigation_reserved4 = 256;
	public static final int sim_navigation_clickselection = 512;
	public static final int sim_navigation_ctrlselection = 1024;
	public static final int sim_navigation_shiftselection = 2048;
	public static final int sim_navigation_camerazoomwheel = 4096;
	public static final int sim_navigation_camerarotaterightbutton = 8192;

	/* Command error codes */
	public static final int simx_error_noerror = 0;
	public static final int simx_error_novalue_flag = 1;		/* input buffer doesn't contain the specified command */
	public static final int simx_error_timeout_flag = 2;		/* command reply not received in time for simx_opmode_oneshot_wait operation mode */
	public static final int simx_error_illegal_opmode_flag = 4;		/* command doesn't support the specified operation mode */
	public static final int simx_error_remote_error_flag = 8;		/* command caused an error on the server side */
	public static final int simx_error_split_progress_flag = 16;		/* previous similar command not yet fully processed (applies to simx_opmode_oneshot_split operation modes) */
	public static final int simx_error_local_error_flag = 32;		/* command caused an error on the client side */
	public static final int simx_error_initialize_error_flag = 64;		/* simxStart was not yet called */


			/* Regular operation modes */
	public static final int	simx_opmode_oneshot = 0;		/* sends command as one chunk. Reply will also come as one chunk. Doesn't wait for the reply. */
	public static final int	simx_opmode_oneshot_wait = 65536;		/* sends command as one chunk. Reply will also come as one chunk. Waits for the reply (_REPLY_WAIT_TIMEOUT_IN_MS is the timeout). */
	public static final int	simx_opmode_streaming = 131072;
	public static final int	simx_opmode_continuous = 131072;

			/* Operation modes for heavy data */
	public static final int	simx_opmode_oneshot_split = 196608;		/* sends command as several chunks (max chunk size is x bytes, where x can be _MIN_SPLIT_AMOUNT_IN_BYTES-65535. Just add x to simx_opmode_oneshot_split). Reply will also come as several chunks. Doesn't wait for the reply. */	 
	public static final int simx_opmode_streaming_split = 262144;
	public static final int simx_opmode_continuous_split = 262144;

			/* Special operation modes */
	public static final int simx_opmode_discontinue = 327680;		/* removes and cancels all commands stored on the client or server side (also continuous commands) */
	public static final int simx_opmode_buffer = 393216;	/* doesn't send anything, but checks if a reply for the given command is available in the input buffer (i.e. previously received from the server) */
	public static final int simx_opmode_remove = 458752;		/* doesn't send anything and doesn't return any specific value. It just erases a similar command reply in the inbox (to free some memory) */

}
class IntW
{
	int w;
	public IntW(int i) { w = i; }
	public void setValue(int i) { w = i; }
	public int getValue() { return w; }
}

class IntWA
{
	int[] w;
	public IntWA(int i) { w = new int[i]; }
	public void initArray(int i) { w = new int[i]; }
	public int getLength() { return w.length; }
	public int[] getNewArray(int i) { w = new int[i]; return w; }
	public int[] getArray() { return w; }
}


class FloatW
{
	float w;
	public FloatW(float f) { w = f; }
	public void setValue(float i) { w = i; }
	public float getValue() { return w; }
}

class FloatWA
{
	float[] w;
	public FloatWA(int i) { w = new float[i]; }
	public void initArray(int i) { w = new float[i]; }
	public float[] getArray() { return w; }
	public int getLength() { return w.length; }
	public float[] getNewArray(int i) { w = new float[i]; for (int k=0; k<i; k++) w[k]=0.0f; return w; }
}

class FloatWAA
{
	FloatWA[] w;
	public FloatWAA(int i) { w = new FloatWA[i]; }
	public void initArray(int i) { w = new FloatWA[i]; }
	public FloatWA[] getArray() { return w; }
	public int getLength() { return w.length; }
	public FloatWA[] getNewArray(int i) { w = new FloatWA[i]; for (int k=0; k<i; k++) w[k]=new FloatWA(1); return w; }
}

class CharW
{
	char w;
	public CharW(char c) { w = c; }
	public void setValue(char c) { w = c; }
	public char getValue() { return w; }
}

class CharWA
{
	char[] w;
	public CharWA(int i) { w = new char[i]; }
	public void initArray(int i) { w = new char[i]; }
	public char[] getArray() { return w; }
	public int getLength() { return w.length; }
	public char[] getNewArray(int i) { w = new char[i]; return w; }
}

class StringW
{
	String w;
	public StringW(String s) { w = new String(s); }
	public void setValue(String s) { w = new String(s); }
	public String getValue() { return w; }
}

class StringWA
{
	String[] w;
	public StringWA(int i) { w = new String[i]; }
	public void initArray(int i) { w = new String[i]; }
	public String[] getArray() { return w; }
	public int getLength() { return w.length; }
	public String[] getNewArray(int i) { w = new String[i]; return w; }
}

class BoolW
{
	boolean w;
	public BoolW(boolean b) { w = b; }
	public void setValue(boolean b) { w = b; }
	public boolean getValue() { return w; }
}

class BoolWA
{
	boolean w[];
	public BoolWA(int i) { w = new boolean[i]; }
	public void initArray(int i) { w = new boolean[i]; }
	public boolean[] getArray() { return w; }
	public int getLength() { return w.length; }
	public boolean[] getNewArray(int i) { w = new boolean[i]; return w; }
}

