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

#include "v_repExtBubbleRob.h"
#include "access.h"
#include <iostream>
#include "v_repLib.h"


#ifdef _WIN32
	#include <shlwapi.h> // required for PathRemoveFileSpec function
	#define WIN_AFX_MANAGE_STATE AFX_MANAGE_STATE(AfxGetStaticModuleState())
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
	#define WIN_AFX_MANAGE_STATE
#endif /* __linux || __APPLE__ */

LIBRARY vrepLib;

void simExtBubbleMoveAndAvoid(SLuaCallBack* p)
{ // Callback of the Lua simExtBubbleMoveAndAvoid command
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	int result=-1; // -1 means error
	float maxVel; // the maximum velocity we might have to return

	if (p->inputArgCount>1)
	{ // Ok, we have at least 2 input arguments
		if ( (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_float)&&(p->inputArgTypeAndSize[1*2+0]==(sim_lua_arg_float|sim_lua_arg_table))&&(p->inputArgTypeAndSize[1*2+1]>=2) )
		{ // Ok, we have one float as argument 1, and a table of floats as argument 2 (table size >=2)
			// Now check if we have the 3rd argument (boolean) that is optional (by default false):
			bool returnDirectly=false; // default value
			if (p->inputArgCount>=3)
			{
				if (p->inputArgTypeAndSize[2*2+0]==sim_lua_arg_bool)
					returnDirectly=p->inputBool[0]!=0;
			}
			if (p->inputFloat[0]<=0.0f)
				returnDirectly=true; // if movement duration is 0
			if (!returnDirectly)
				p->waitUntilZero=1; // the effect of this is that when we leave the callback, the Lua script gets control
									// back only when this value turns zero. This allows for "blocking" functions 

			// Now get the CBubbleRob object associated with BubbleRob:
			CBubbleRob* bubbleRob=CAccess::bubbleRobContainer->getFromAssociatedObject(p->objectID);
			if (bubbleRob!=NULL)
			{ // Ok we found the associated CBubbleObject

				// Now execute the command:
				float backRelativeVelocities[2]={p->inputFloat[1],p->inputFloat[2]};
				bubbleRob->moveAndAvoid(p->inputFloat[0],backRelativeVelocities,&p->waitUntilZero);
				result=1; // function executed successfully
				maxVel=bubbleRob->getMaxVelocity();
			}
			else
				simSetLastError("simExtBubbleMoveAndAvoid","BubbleRob tag was not found."); // output an error
		}
		else
			simSetLastError("simExtBubbleMoveAndAvoid","Wrong argument type/size."); // output an error
	}
	else
		simSetLastError("simExtBubbleMoveAndAvoid","Not enough arguments."); // output an error

	// Now we prepare the return value(s):
	if (result==-1)
		p->outputArgCount=1; // 1 return value (function failed)
	else
		p->outputArgCount=2; // 2 return values (function succeeded)

	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)

	if (result!=-1)
	{
		p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_float;	// The second return value is a float
		p->outputArgTypeAndSize[2*1+1]=1;					// Not used (table size if the return value was a table)

		p->outputFloat=(simFloat*)simCreateBuffer(1*sizeof(maxVel)); // 1 float return value
		p->outputFloat[0]=maxVel; // This is the float value we want to return
	}

	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(result)); // 1 integer return value
	p->outputInt[0]=result; // This is the integer value we want to return

	simLockInterface(0);
}

void simExtBubbleStop(SLuaCallBack* p)
{ // Callback of the Lua simExtBubbleStop command
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	int result=-1; // -1 means error

	// Now get the CBubbleRob object associated with BubbleRob:
	CBubbleRob* bubbleRob=CAccess::bubbleRobContainer->getFromAssociatedObject(p->objectID);
	if (bubbleRob!=NULL)
	{ // Ok we found the associated CBubbleObject, now execute the command
		bubbleRob->stop(); 
		result=1; // execution was successful
	}
	else
		simSetLastError("simExtBubbleStop","BubbleRob tag was not found."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(1*2*sizeof(simInt)); // 1 return value takes 2 simInt for the type and size buffer

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;	// The return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;				// Not used (table size if the return value was a table)

	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(result)); // 1 integer return value
	p->outputInt[0]=result; // This is the integer value we want to return

	simLockInterface(0);
}

VREP_DLLEXPORT unsigned char v_repStart(void* reservedPointer,int reservedInt)
{ // This is called just once, at the start of V-REP.
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
		std::cout << "Error, could not find or correctly load v_rep.dll. Cannot start 'BubbleRob' plugin.\n";
		return(0); // Means error, V-REP will unload this plugin
	}
	if (getVrepProcAddresses(vrepLib)==0)
	{
		std::cout << "Error, could not find all required functions in v_rep.dll. Cannot start 'BubbleRob' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}

	// Check the V-REP version:
	int vrepVer;
	simGetIntegerParameter(sim_intparam_program_version,&vrepVer);
	if (vrepVer<20600) // if V-REP version is smaller than 2.06.00
	{
		std::cout << "Sorry, your V-REP copy is somewhat old, V-REP 2.6.0 or higher is required. Cannot start 'BubbleRob' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}

	// Do the normal plugin initialization:
	simLockInterface(1);

	CAccess::createNonGui();
	CAccess::createGui();

	// Register two new Lua commands:
	int inArgs1[]={3,sim_lua_arg_float,sim_lua_arg_float|sim_lua_arg_table,sim_lua_arg_bool}; // 3 input arguments: one float (duration of automatic movement) AND one array of floats (relative backward velocity) AND one boolean value (wether the function is blocking)
	simRegisterCustomLuaFunction("simExtBubbleMoveAndAvoid","number result,number maxVelocity=simExtBubbleMoveAndAvoid(number duration,table_2 backRelativeVelocities,boolean returnDirectly=false)",inArgs1,simExtBubbleMoveAndAvoid);

	int inArgs2[]={0}; // no input arguments
	simRegisterCustomLuaFunction("simExtBubbleStop","number result=simExtBubbleStop()",inArgs2,simExtBubbleStop);

	// Here you could also register custom Lua variables with simRegisterCustomLuaVariable

	simLockInterface(0);
	return(4); // initialization went fine, we return the version number of this plugin (can be queried with simGetModuleName)
	// version 1 was for V-REP versions before V-REP 2.5.12
	// version 2 was for V-REP versions before V-REP 2.6.0
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
		if (auxiliaryData[0]==CAccess::bubbleRobDialog->dialogMenuItemHandle)
			CAccess::bubbleRobDialog->setVisible(!CAccess::bubbleRobDialog->getVisible()); // Toggle visibility of the dialog
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
			CAccess::bubbleRobContainer->actualizeForSceneContent(); 
			refreshDlgFlag=true;
		}
	}

	if (message==sim_message_eventcallback_moduleopen)
	{ // A script called simOpenModule (by default the main script). Is only called during simulation.
		if ( (customData==NULL)||(_stricmp("BubbleRob",(char*)customData)==0) ) // is the command also meant for BubbleRob?
			CAccess::bubbleRobContainer->startOfSimulation();				// yes!
	}

	if (message==sim_message_eventcallback_modulehandle)
	{ // A script called simHandleModule (by default the main script). Is only called during simulation.
		if ( (customData==NULL)||(_stricmp("BubbleRob",(char*)customData)==0) ) // is the command also meant for BubbleRob?
			CAccess::bubbleRobContainer->handleSimulation();					// yes!
	}

	if (message==sim_message_eventcallback_moduleclose)
	{ // A script called simCloseModule (by default the main script). Is only called during simulation.
		if ( (customData==NULL)||(_stricmp("BubbleRob",(char*)customData)==0) ) // is the command also meant for BubbleRob?
			CAccess::bubbleRobContainer->endOfSimulation();					// yes!
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
		CAccess::bubbleRobDialog->refresh(); // Refresh the dialog
#endif // _WIN32
		refreshDlgFlag=false;
	}

	simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings
	simLockInterface(0);
	return(retVal);
}
