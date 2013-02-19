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

#include "stdafx.h"
#include "v_repExtRemoteApi.h"
#include "v_repLib.h"
#include <iostream>
#include "simxConnections.h"
#include "confReader.h"
#include <sstream>

#ifdef _WIN32
	#include <shlwapi.h> // required for PathRemoveFileSpec function
	#define WIN_AFX_MANAGE_STATE AFX_MANAGE_STATE(AfxGetStaticModuleState())
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
	#define WIN_AFX_MANAGE_STATE
#endif /* __linux || __APPLE__ */


#define PLUGIN_VERSION 1
#define CONCAT(x,y,z) x y z
#define strConCat(x,y,z)	CONCAT(x,y,z)
#define LUA_START_COMMAND "simExtRemoteApiStart"
#define LUA_STOP_COMMAND "simExtRemoteApiStop"
#define LUA_STATUS_COMMAND "simExtRemoteApiStatus"

LIBRARY vrepLib;
CSimxConnections allConnections;

void LUA_STATUS_COMMAND_CALLBACK(SLuaCallBack* p)
{ // the callback function of the new Lua command
	simLockInterface(1);

	int result=-1; // error or no connection at given index
	int info[5];

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have (at least) 1 int as argument
			CSimxSocket* s=allConnections.getConnectionAtIndex(p->inputInt[0]);
			if (s!=NULL)
			{
				result=s->getStatus();
				s->getInfo(info);
			}
		}
		else
			simSetLastError(LUA_STATUS_COMMAND,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_STATUS_COMMAND,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	if (result>-1)
	{
		p->outputArgCount=2; // 2 return values
		p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
		p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;	// The return value is an int
		p->outputArgTypeAndSize[2*0+1]=1;				// Not used (table size if the return value was a table)
		p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_int|sim_lua_arg_table;	// The return value is an int table
		p->outputArgTypeAndSize[2*1+1]=5;				// Table size
		p->outputInt=(simInt*)simCreateBuffer(6*sizeof(result)); // total of 6 ints
		p->outputInt[0]=result; // This is the int value we want to return (arg 1)
		// Now the table values:
		for (int i=0;i<5;i++)
			p->outputInt[1+i]=info[i];
	}
	else
	{
		p->outputArgCount=1; // 1 return value
		p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
		p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;	// The return value is an int
		p->outputArgTypeAndSize[2*0+1]=1;				// Not used (table size if the return value was a table)
		p->outputInt=(simInt*)simCreateBuffer(1*sizeof(result)); // 1 int return value
		p->outputInt[0]=result; // This is the int value we want to return
	}
	simLockInterface(0);
}

void LUA_START_COMMAND_CALLBACK(SLuaCallBack* p)
{ // the callback function of the new Lua command
	simLockInterface(1);

	int result=-1; // error

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have (at least) 1 int as argument
			bool err=false;
			int maxPacketSize=250;
			bool debug=false;
			if (p->inputArgCount>1)
			{
				if (p->inputArgTypeAndSize[1*2+0]==sim_lua_arg_int)
					maxPacketSize=p->inputInt[1];
				else
					err=true;
				if (p->inputArgCount>2)
				{
					if (p->inputArgTypeAndSize[2*2+0]==sim_lua_arg_bool)
						debug=(p->inputBool[0]!=0);
					else
						err=true;
				}
			}
			if (!err)
			{ 
				CSimxSocket* s=allConnections.getConnectionFromPort(p->inputInt[0]);
				if (s==NULL)
				{
					CSimxSocket* oneSocketConnection=new CSimxSocket(p->inputInt[0],true,debug,maxPacketSize,false);
					oneSocketConnection->start();
					allConnections.addSocketConnection(oneSocketConnection);
					result=1;
				}
				else
					simSetLastError(LUA_START_COMMAND,"Invalid port number."); // output an error
			}
			else
				simSetLastError(LUA_START_COMMAND,"Wrong argument type/size."); // output an error
		}
		else
			simSetLastError(LUA_START_COMMAND,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_START_COMMAND,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;	// The return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;				// Not used (table size if the return value was a table)
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(result)); // 1 int return value
	p->outputInt[0]=result; // This is the int value we want to return

	simLockInterface(0);
}

void LUA_STOP_COMMAND_CALLBACK(SLuaCallBack* p)
{ // the callback function of the new Lua command
	simLockInterface(1);

	int result=-1; // error

	if (p->inputArgCount>0)
	{ // Ok, we have at least 1 input argument
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{ // Ok, we have (at least) 1 int as argument
			CSimxSocket* s=allConnections.getConnectionFromPort(p->inputInt[0]);
			if ( (s!=NULL)&&s->getActiveOnlyDuringSimulation() )
			{
				allConnections.removeSocketConnection(s);
				result=1;
			}
			else
				simSetLastError(LUA_STOP_COMMAND,"Invalid port number."); // output an error
		}
		else
			simSetLastError(LUA_STOP_COMMAND,"Wrong argument type/size."); // output an error
	}
	else
		simSetLastError(LUA_STOP_COMMAND,"Not enough arguments."); // output an error

	// Now we prepare the return value:
	p->outputArgCount=1; // 1 return value
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;	// The return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;				// Not used (table size if the return value was a table)
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(result)); // 1 int return value
	p->outputInt[0]=result; // This is the int value we want to return

	simLockInterface(0);
}


// This is the plugin start routine:
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
		std::cout << "Error, could not find or correctly load the V-REP library. Cannot start 'RemoteApi' plugin.\n";
		return(0); // Means error, V-REP will unload this plugin
	}
	if (getVrepProcAddresses(vrepLib)==0)
	{
		std::cout << "Error, could not find all required functions in the V-REP library. Cannot start 'RemoteApi' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}

	int vrepVer;
	simGetIntegerParameter(sim_intparam_program_version,&vrepVer);
	if (vrepVer<20604) // if V-REP version is smaller than 2.06.04
	{
		std::cout << "Sorry, your V-REP copy is somewhat old. Cannot start 'RemoteApi' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}
	simLockInterface(1);

	// Register 3 new Lua commands:
	int inArgs1[]={1,sim_lua_arg_int};
	simRegisterCustomLuaFunction(LUA_STATUS_COMMAND,strConCat("number status,table_5 info=",LUA_STATUS_COMMAND,"(number socketConnectionIndex)"),inArgs1,LUA_STATUS_COMMAND_CALLBACK);
	int inArgs2[]={3,sim_lua_arg_int,sim_lua_arg_int,sim_lua_arg_bool};
	simRegisterCustomLuaFunction(LUA_START_COMMAND,strConCat("number result=",LUA_START_COMMAND,"(number socketPort,number maxPacketSize=250,boolean debug=false)"),inArgs2,LUA_START_COMMAND_CALLBACK);
	simRegisterCustomLuaFunction(LUA_STOP_COMMAND,strConCat("number result=",LUA_STOP_COMMAND,"(number socketPort)"),inArgs1,LUA_STOP_COMMAND_CALLBACK);

	// Read the configuration file to prepare socket connections:
	CConfReader conf;
	temp=currentDirAndPath;

#ifdef _WIN32
	temp+="\\remoteApiConnections.txt";
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
	temp+="/remoteApiConnections.txt";
#endif /* __linux || __APPLE__ */

	conf.readConfiguration(temp.c_str());
	int index=1;
	while (true)
	{
		std::stringstream strStream;
		strStream << index;
		std::string variableNameBase("portIndex");
		variableNameBase+=strStream.str();
		std::string variableName=variableNameBase+"_port";
		int portNb;
		if (conf.getInteger(variableName.c_str(),portNb))
		{
			bool debug=false;
			int maxPacketSize=250;
			bool synchronousTrigger=false;
			variableName=variableNameBase+"_maxPacketSize";
			conf.getInteger(variableName.c_str(),maxPacketSize);
			variableName=variableNameBase+"_debug";
			conf.getBoolean(variableName.c_str(),debug);
			variableName=variableNameBase+"_syncSimTrigger";
			conf.getBoolean(variableName.c_str(),synchronousTrigger);
			if (allConnections.getConnectionFromPort(portNb)==NULL)
			{
				synchronousTrigger&=(allConnections.getSynchronousSimulationTriggerConnection()==NULL);
				CSimxSocket* oneSocketConnection=new CSimxSocket(portNb,false,debug,maxPacketSize,synchronousTrigger);
				oneSocketConnection->start();
				allConnections.addSocketConnection(oneSocketConnection);
				if (synchronousTrigger)
					allConnections.setSynchronousSimulationTriggerConnection(oneSocketConnection); // only one connection can act as trigger!
				std::cout << "Starting a remote API server on port " << portNb << std::endl;
			}
			else
				std::cout << "Failed starting a remote API server on port " << portNb << std::endl;
			index++;
		}
		else
			break;
	}

	simLockInterface(0);
	return(PLUGIN_VERSION); // initialization went fine, we return the version number of this extension module (can be queried with simGetModuleName)
}

// This is the plugin end routine:
VREP_DLLEXPORT void v_repEnd()
{ // This is called just once, at the end of V-REP
	WIN_AFX_MANAGE_STATE;

	allConnections.removeAllConnections();

	unloadVrepLibrary(vrepLib); // release the library
}

// This is the plugin messaging routine (i.e. V-REP calls this function very often, with various messages):
VREP_DLLEXPORT void* v_repMessage(int message,int* auxiliaryData,void* customData,int* replyData)
{ // This is called quite often. Just watch out for messages/events you want to handle
	WIN_AFX_MANAGE_STATE;
	simLockInterface(1);

	// This function should not generate any error messages:
	int errorModeSaved;
	simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
	simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);

	void* retVal=NULL;

	if (message==sim_message_eventcallback_instancepass)
	{ // This message is sent each time the scene was rendered (well, shortly after) (very often)
		allConnections.instancePass();
	}

	if (message==sim_message_eventcallback_mainscriptabouttobecalled)
	{ // Main script is about to be run
		if (allConnections.mainScriptAboutToBeCalled())
			replyData[0]=0; // this tells V-REP that we don't wanna execute the main script
	}

	if (message==sim_message_eventcallback_simulationended)
	{ // Simulation just ended
		allConnections.simulationEnded();
	}

	simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings
	simLockInterface(0);
	return(retVal);
}

