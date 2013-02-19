// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// -------------------------------------------------------------------
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// 
// You are free to use/modify/distribute this file for whatever purpose!
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

#include "stdafx.h"
#include "v_repExtK3.h"
#include "v_repLib.h"
#include "access.h"
#include <iostream>
#include "porting.h"

#ifdef _WIN32
	#include <shlwapi.h> // required for PathRemoveFileSpec function
	#define WIN_AFX_MANAGE_STATE AFX_MANAGE_STATE(AfxGetStaticModuleState())
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
	#define WIN_AFX_MANAGE_STATE
#endif /* __linux || __APPLE__ */

#define CONCAT(x,y,z) x y z
#define strConCat(x,y,z)	CONCAT(x,y,z)

#define LUA_GET_INFRARED "simExtK3_getInfrared"
#define LUA_GET_ULTRASONIC "simExtK3_getUltrasonic"
#define LUA_GET_LINE_SENSOR "simExtK3_getLineSensor"
#define LUA_SET_VELOCITY "simExtK3_setVelocity"
#define LUA_SET_ARM_POSITION "simExtK3_setArmPosition"
#define LUA_GET_GRIPPER_SENSOR_DIST "simExtK3_getGripperProxSensor"
#define LUA_SET_GRIPPER_GAP "simExtK3_setGripperGap"
#define LUA_GET_ENCODER "simExtK3_getEncoder"
#define LUA_SET_ENCODERS "simExtK3_setEncoders"

LIBRARY vrepLib;

void LUA_GET_INFRARED_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	float result=-1.0f; // negative number means error

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have one int as argument 1
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				result=k3->getInfrared(p->inputInt[0]);
			}
			else
				simSetLastError(LUA_GET_INFRARED,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_GET_INFRARED,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_GET_INFRARED,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_float;	// The return value is a float
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputFloat=(simFloat*)simCreateBuffer(1*sizeof(result)); // 1 float return value
	p->outputFloat[0]=result; // This is the float value we want to return

	simLockInterface(0);
}

void LUA_GET_ULTRASONIC_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	float result=-1.0f; // negative number means error

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have one int as argument 1
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				result=k3->getUltrasonic(p->inputInt[0]);
			}
			else
				simSetLastError(LUA_GET_ULTRASONIC,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_GET_ULTRASONIC,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_GET_ULTRASONIC,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_float;	// The return value is a float
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputFloat=(simFloat*)simCreateBuffer(1*sizeof(result)); // 1 float return value
	p->outputFloat[0]=result; // This is the float value we want to return

	simLockInterface(0);
}

void LUA_GET_LINE_SENSOR_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	float result=-1.0f; // negative number means error

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have one int as argument 1
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				result=k3->getLineSensor(p->inputInt[0]);
			}
			else
				simSetLastError(LUA_GET_LINE_SENSOR,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_GET_LINE_SENSOR,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_GET_LINE_SENSOR,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_float;	// The return value is a float
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputFloat=(simFloat*)simCreateBuffer(1*sizeof(result)); // 1 float return value
	p->outputFloat[0]=result; // This is the float value we want to return

	simLockInterface(0);
}

void LUA_SET_VELOCITY_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	if (p->inputArgCount>1)
	{ // Ok, we have at least 2 input argument
		if ( (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_float)&&(p->inputArgTypeAndSize[1*2+0]==sim_lua_arg_float) )
		{ // Ok, we have 2 floats as argument 1&2
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				k3->setVelocity(p->inputFloat[0],p->inputFloat[1]);
			}
			else
				simSetLastError(LUA_SET_VELOCITY,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_SET_VELOCITY,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_SET_VELOCITY,"Not enough arguments."); // output an error

	p->outputArgCount=0; // no return values!

	simLockInterface(0);
}

void LUA_SET_ARM_POSITION_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have one int as argument 1
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				k3->setArmPosition(p->inputInt[0]);
			}
			else
				simSetLastError(LUA_SET_ARM_POSITION,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_SET_ARM_POSITION,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_SET_ARM_POSITION,"Not enough arguments."); // output an error

	p->outputArgCount=0; // 0 return values

	simLockInterface(0);
}

void LUA_GET_GRIPPER_SENSOR_DIST_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	float result=-1.0f; // negative number means error

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have one int as argument 1
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				result=k3->getFingerProxSensor(p->inputInt[0]);
			}
			else
				simSetLastError(LUA_GET_GRIPPER_SENSOR_DIST,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_GET_GRIPPER_SENSOR_DIST,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_GET_GRIPPER_SENSOR_DIST,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_float;	// The return value is a float
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputFloat=(simFloat*)simCreateBuffer(1*sizeof(result)); // 1 float return value
	p->outputFloat[0]=result; // This is the float value we want to return

	simLockInterface(0);
}

void LUA_SET_GRIPPER_GAP_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have one int as argument 1
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				k3->setGripperGap(p->inputInt[0]);
			}
			else
				simSetLastError(LUA_SET_GRIPPER_GAP,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_SET_GRIPPER_GAP,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_SET_GRIPPER_GAP,"Not enough arguments."); // output an error

	p->outputArgCount=0; // 0 return values

	simLockInterface(0);
}

void LUA_GET_ENCODER_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	bool error=true;
	int result;
	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have one int as argument 1
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				result=k3->getEncoder(p->inputInt[0]);
				error=false;
			}
			else
				simSetLastError(LUA_GET_ENCODER,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_GET_ENCODER,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_GET_ENCODER,"Not enough arguments."); // output an error

	if (!error)
	{	// Now we prepare the return value:
		p->outputArgCount=1; // 1 return value
		p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
		p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;	// The return value is an int
		p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
		p->outputInt=(simInt*)simCreateBuffer(1*sizeof(result)); // 1 float return value
		p->outputInt[0]=result; // This is the int value we want to return
	}
	else
		p->outputArgCount=0; // 0 return values --> nil to indicate an error


	simLockInterface(0);
}

void LUA_SET_ENCODERS_CALLBACK(SLuaCallBack* p)
{
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	bool error=true;
	if (p->inputArgCount>1)
	{ // Ok, we have at least 2 input argument
		if ( (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)&&(p->inputArgTypeAndSize[1*2+0]==sim_lua_arg_int) )
		{ // Ok, we have two ints as argument 1 & 2
			// Now get the K3 object associated with Khepera3:
			CK3* k3=CAccess::k3Container->getFromAssociatedObject(p->objectID);
			if (k3!=NULL)
			{ // Ok we found the associated CK3
				k3->setEncoders(p->inputInt[0],p->inputInt[1]);
				error=false;
			}
			else
				simSetLastError(LUA_SET_ENCODERS,"K3 tag was not found."); // output an error
		}
		else
			simSetLastError(LUA_SET_ENCODERS,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_SET_ENCODERS,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_bool;	// The return value is a bool
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputBool=(simBool*)simCreateBuffer(1*sizeof(simBool)); // 1 simBool return value
	if (error)
		p->outputBool[0]=0;
	else
		p->outputBool[0]=1;


	simLockInterface(0);
}

VREP_DLLEXPORT unsigned char v_repStart(void* reservedPointer,int reservedInt)
{ // This is called just once, at the start of V-REP
	WIN_AFX_MANAGE_STATE;

	// Dynamically load and bind V-REP functions:
	char curDirAndFile[1024];
#ifdef _WIN32
	GetModuleFileName(NULL,curDirAndFile,1023);
	PathRemoveFileSpec(curDirAndFile);
#elif defined (__linux) || defined (__APPLE__)
	getcwd(curDirAndFile, sizeof(curDirAndFile));
#endif

	std::string currentDirAndPath(curDirAndFile);
	std::string temp(currentDirAndPath);

#ifdef _WIN32
	temp+="\\v_rep.dll";
#elif defined (__linux)
	temp+="/libv_rep.so";
#elif defined (__APPLE__)
	temp+="/libv_rep.dylib";
#endif /* __linux || __APPLE__ */

	vrepLib=loadVrepLibrary(temp.c_str());
	if (vrepLib==NULL)
	{
		std::cout << "Error, could not find or correctly load v_rep.dll. Cannot start 'K3' plugin.\n";
		return(0); // Means error, V-REP will unload this plugin
	}
	if (getVrepProcAddresses(vrepLib)==0)
	{
		std::cout << "Error, could not find all required functions in v_rep.dll. Cannot start 'K3' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}

	// Check the V-REP version:
	int vrepVer;
	simGetIntegerParameter(sim_intparam_program_version,&vrepVer);
	if (vrepVer<20600) // if V-REP version is smaller than 2.06.00
	{
		std::cout << "Sorry, your V-REP copy is somewhat old, V-REP 2.6.0 or later is required. Cannot start 'K3' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}

	// Do the normal plugin initialization:
	simLockInterface(1);

	CAccess::createNonGui();
	CAccess::createGui();

	// Register new Lua commands:
	int inArgs1[]={1,sim_lua_arg_int};
	simRegisterCustomLuaFunction(LUA_GET_INFRARED,strConCat("number distance=",LUA_GET_INFRARED,"(number index)"),inArgs1,LUA_GET_INFRARED_CALLBACK);
	simRegisterCustomLuaFunction(LUA_GET_ULTRASONIC,strConCat("number distance=",LUA_GET_ULTRASONIC,"(number index)"),inArgs1,LUA_GET_ULTRASONIC_CALLBACK);
	simRegisterCustomLuaFunction(LUA_GET_LINE_SENSOR,strConCat("number intensity=",LUA_GET_LINE_SENSOR,"(number index)"),inArgs1,LUA_GET_LINE_SENSOR_CALLBACK);
	simRegisterCustomLuaFunction(LUA_SET_ARM_POSITION,strConCat("",LUA_SET_ARM_POSITION,"(number position)"),inArgs1,LUA_SET_ARM_POSITION_CALLBACK);
	simRegisterCustomLuaFunction(LUA_SET_GRIPPER_GAP,strConCat("",LUA_SET_GRIPPER_GAP,"(number gap)"),inArgs1,LUA_SET_GRIPPER_GAP_CALLBACK);
	simRegisterCustomLuaFunction(LUA_GET_GRIPPER_SENSOR_DIST,strConCat("number distance=",LUA_GET_GRIPPER_SENSOR_DIST,"(number index)"),inArgs1,LUA_GET_GRIPPER_SENSOR_DIST_CALLBACK);
	simRegisterCustomLuaFunction(LUA_GET_ENCODER,strConCat("number encoderValue=",LUA_GET_ENCODER,"(number index)"),inArgs1,LUA_GET_ENCODER_CALLBACK);
	
	int inArgs2[]={2,sim_lua_arg_float,sim_lua_arg_float};
	simRegisterCustomLuaFunction(LUA_SET_VELOCITY,strConCat("",LUA_SET_VELOCITY,"(number leftVel,number rightVel)"),inArgs2,LUA_SET_VELOCITY_CALLBACK);

	int inArgs3[]={2,sim_lua_arg_int,sim_lua_arg_int};
	simRegisterCustomLuaFunction(LUA_SET_ENCODERS,strConCat("boolean result=",LUA_SET_ENCODERS,"(number leftEncoder,number rightEncoder)"),inArgs3,LUA_SET_ENCODERS_CALLBACK);
	

	simLockInterface(0);
	return(3); // initialization went fine, we return the version number of this plugin (can be queried with simGetModuleName)
	// version 1 was for V-REP 2.5.11 and below
	// version 2 was for V-REP 2.5.12 and below
}

VREP_DLLEXPORT void v_repEnd()
{ // This is called just once, at the end of V-REP
	WIN_AFX_MANAGE_STATE;

	CAccess::destroyGui();
	CAccess::destroyNonGui();

	unloadVrepLibrary(vrepLib); // release the library
}

VREP_DLLEXPORT void* v_repMessage(int message,int* auxiliaryData,void* customData,int* replyData)
{ // This is called quite often. Just watch out for messages/events you want to handle
	WIN_AFX_MANAGE_STATE;

	simLockInterface(1);
	static bool refreshDlgFlag=true;

	// This function should not generate any error messages:
	int errorModeSaved;
	simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
	simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);

	void* retVal=NULL;
	if (message==sim_message_eventcallback_refreshdialogs)
		refreshDlgFlag=true; // V-REP dialogs were refreshed. Maybe a good idea to refresh this plugin's dialog too

	if (message==sim_message_eventcallback_menuitemselected)
	{ // A custom menu bar entry was selected..
#ifdef _WIN32 // only the Windows version has a dialog!
		if (auxiliaryData[0]==CAccess::k3Dialog->dialogMenuItemHandle)
			CAccess::k3Dialog->setVisible(!CAccess::k3Dialog->getVisible()); // Toggle visibility of the dialog
#endif // _WIN32
	}

	if (message==sim_message_eventcallback_instancepass)
	{ // It is important to always correctly react to events in V-REP. This message is the most convenient way to do so:

		int flags=auxiliaryData[0];
		bool sceneContentChanged=((flags&(1+2+4+8+16+32+64+256))!=0); // object erased, created, model or scene loaded, und/redo called, instance switched, or object scaled since last sim_message_eventcallback_instancepass message 
		bool instanceSwitched=((flags&64)!=0);

		if (instanceSwitched)
		{
			// React to an instance switch here!!
		}

		if (sceneContentChanged)
		{ // we actualize plugin objects for changes in the scene
			CAccess::k3Container->actualizeForSceneContent(); 
			refreshDlgFlag=true;
		}
	}

	if (message==sim_message_eventcallback_moduleopen)
	{ // A script called simOpenModule (by default the main script). Is only called during simulation.
		if ( (customData==NULL)||(_stricmp("K3",(char*)customData)==0) ) // is the command also meant for K3?
			CAccess::k3Container->startOfSimulation();				// yes!
	}

	if (message==sim_message_eventcallback_modulehandle)
	{ // A script called simHandleModule (by default the main script). Is only called during simulation.
		if ( (customData==NULL)||(_stricmp("K3",(char*)customData)==0) ) // is the command also meant for K3?
			CAccess::k3Container->handleSimulation();					// yes!
	}

	if (message==sim_message_eventcallback_moduleclose)
	{ // A script called simCloseModule (by default the main script). Is only called during simulation.
		if ( (customData==NULL)||(_stricmp("K3",(char*)customData)==0) ) // is the command also meant for K3?
			CAccess::k3Container->endOfSimulation();					// yes!
	}

	if (message==sim_message_eventcallback_instanceswitch)
	{ // Here the user switched the instance. React to this message in a similar way as you would react to a full
	  // scene content change. In this plugin example, we react to an instance switch by reacting to the
	  // sim_message_eventcallback_instancepass message and checking the bit 6 (64) of the auxiliaryData[0]
	  // (see here above)

	}

	if (message==sim_message_eventcallback_broadcast)
	{ // Here we have a plugin that is broadcasting data (the broadcaster will also receive this data!)

	}

	if (message==sim_message_eventcallback_scenesave)
	{ // The scene is about to be saved. If required do some processing here (e.g. add custom scene data to be serialized with the scene)

	}

	if (message==sim_message_eventcallback_simulationabouttostart)
	{ // Simulation is about to start

	}

	if (message==sim_message_eventcallback_simulationended)
	{ // Simulation just ended

	}

	// You can add more messages to handle here

	if ((message==sim_message_eventcallback_guipass)&&refreshDlgFlag)
	{ // handle refresh of the plugin's dialog:
#ifdef _WIN32 // only the Windows version has a dialog!
		CAccess::k3Dialog->refresh(); // Refresh the dialog
#endif // _WIN32
		refreshDlgFlag=false;
	}

	simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings
	simLockInterface(0);
	return(retVal);
}
