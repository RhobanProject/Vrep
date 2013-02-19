// This file is part of V-REP, the Virtual Robot Experimentation Platform.
// 
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// V-REP is dual-licensed, under the terms of EITHER (at your option):
//   1. V-REP commercial license (contact us for details)
//   2. GNU GPL (see below)
// 
// GNU GPL license:
// -------------------------------------------------------------------
// V-REP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// V-REP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with V-REP.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

#pragma message("Adding library: shlwapi.lib")	 
#pragma comment(lib,"shlwapi.lib")

#pragma message("Adding library: winmm.lib")	 
#pragma comment(lib,"winmm.lib")

#include <vector>
#include "v_repLib.h"

#include <Mmsystem.h>
#include <shlwapi.h>
#define WINDOWS_VREP

#include <iostream>

#define TIMER_RESOLUTION_IN_MS (1) // set to 0 for default timer swapping operation (coarse-grained)
#define MIN_VAL(a,b) (((a)<(b)) ? (a) : (b))
#define MAX_VAL(a,b) (((a)>(b)) ? (a) : (b))

std::vector<int> pluginHandles;
std::string argument1;

void simulatorInit()
{
	std::cout << "Simulator launched.\n";

	char curDirAndFile[1024];
	GetModuleFileName(NULL,curDirAndFile,1023);
	PathRemoveFileSpec(curDirAndFile);
	std::string currentDirAndPath(curDirAndFile);
	std::string temp(currentDirAndPath);
	temp+="\\v_repExt*.dll";
	WIN32_FIND_DATA fData;
	HANDLE h=FindFirstFile(temp.c_str(),&fData);
	while (h!=INVALID_HANDLE_VALUE)
	{
		std::string tmp;
		int i=8;
		while (fData.cFileName[i]!='.')
			tmp+=fData.cFileName[i++];
		std::string tmp2(currentDirAndPath);
		tmp2+="\\";
		tmp2+=fData.cFileName;

		if (tmp.length()==0)
			tmp="VrepExt"; // This is the extension module of v_rep (exception in naming)!
		bool underscoreFound=false;
		for (int i=0;i<int(tmp.length());i++)
		{
			if (tmp[i]=='_')
				underscoreFound=true;
		}
		if (!underscoreFound)
		{
			std::cout << "Plugin '" << tmp.c_str() << "': loading...\n";
			int pluginHandle=simLoadModule(tmp2.c_str(),tmp.c_str());
			if (pluginHandle==-3)
				std::cout << "Plugin '" << tmp.c_str() << "': load failed (could not load). The plugin probably couldn't load dependency libraries.\n";
			if (pluginHandle==-2)
				std::cout << "Plugin '" << tmp.c_str() << "': load failed (missing entry points).\n";
			if (pluginHandle==-1)
				std::cout << "Plugin '" << tmp.c_str() << "': load failed (failed initialization).\n";
			if (pluginHandle>=0)
			{
				std::cout << "Plugin '" << tmp.c_str() << "': load succeeded.\n";
				pluginHandles.push_back(pluginHandle);
			}
		}
		if (FindNextFile(h,&fData)==0)
			break;
	}
	FindClose(h);


	if (argument1.length()!=0)
	{ // Here we double-clicked a V-REP file or dragged-and-dropped it onto this application
		int l=int(argument1.length());
		if ((l>4)&&(argument1[l-4]=='.')&&(argument1[l-3]=='t')&&(argument1[l-2]=='t'))
		{
			simSetBooleanParameter(sim_boolparam_scene_and_model_load_messages,1);
			if (argument1[l-1]=='t') // trying to load a scene?
			{
				if (simLoadScene(argument1.c_str())==-1)
					simAddStatusbarMessage("Scene could not be opened.");
			}
			if (argument1[l-1]=='m') // trying to load a model?
			{
				if (simLoadModel(argument1.c_str())==-1)
					simAddStatusbarMessage("Model could not be loaded.");
			}
			if (argument1[l-1]=='b') // trying to load a UI?
			{
				if (simLoadUI(argument1.c_str(),0,NULL)==-1)
					simAddStatusbarMessage("UI could not be loaded.");
			}
			simSetBooleanParameter(sim_boolparam_scene_and_model_load_messages,0);
		}
	}
}

void simulatorLoop()
{	// The main application loop (excluding the GUI part)

	int auxValues[4];
	int messageID=0;
	int dataSize;
	while (messageID!=-1)
	{
		simChar* data=simGetSimulatorMessage(&messageID,auxValues,&dataSize);
		if (messageID!=-1)
		{
			if (messageID==sim_message_simulation_start_resume_request)
				simStartSimulation();
			if (messageID==sim_message_simulation_pause_request)
				simPauseSimulation();
			if (messageID==sim_message_simulation_stop_request)
				simStopSimulation();
			if (data!=NULL)
				simReleaseBuffer(data);
		}
	}

	// Handle a running simulation:
	if ( (simGetSimulationState()&sim_simulation_advancing)!=0 )
	{
		if ( (simGetRealTimeSimulation()!=1)||(simIsRealTimeSimulationStepNeeded()==1) )
		{
			if ((simHandleMainScript()&sim_script_main_script_not_called)==0)
				simAdvanceSimulationByOneStep();
		}
	}
}

void simulatorDeinit()
{
	// Unload all plugins:
	for (int i=0;i<int(pluginHandles.size());i++)
		simUnloadModule(pluginHandles[i]);
	pluginHandles.clear();
	std::cout << "Simulator ended.\n";
}

int main(int argc, char* argv[])
{
	if (TIMER_RESOLUTION_IN_MS>0)
	{
		TIMECAPS tc;
		UINT wTimerRes;
		if (timeGetDevCaps(&tc,sizeof(TIMECAPS))==TIMERR_NOERROR) 
		{
			wTimerRes=MIN_VAL(MAX_VAL(tc.wPeriodMin,TIMER_RESOLUTION_IN_MS),tc.wPeriodMax);
			timeBeginPeriod(wTimerRes); 
		}
	}

	char curDirAndFile[1024];
	GetModuleFileName(NULL,curDirAndFile,1023);
	PathRemoveFileSpec(curDirAndFile);
	std::string currentDirAndPath(curDirAndFile);
	std::string temp(currentDirAndPath);
	temp+="\\v_rep.dll";
	LIBRARY lib=loadVrepLibrary(temp.c_str());
	bool wasRunning=false;
	if (lib!=NULL)
	{
		if (getVrepProcAddresses(lib)!=0)
		{
			if (argc>1)
				argument1=argv[1];
			else
				argument1.clear();

			if (simRunSimulator("V-REP",sim_gui_all,simulatorInit,simulatorLoop,simulatorDeinit)!=1)
				printf("Failed initializing and running V-REP\n");
			else
				wasRunning=true;
		}
		else
			printf("Error: could not find all required functions in v_rep.dll\n");
		unloadVrepLibrary(lib);
	}
	else
		printf("Error: could not find or correctly load v_rep.dll\n");
	if (!wasRunning)
		getchar();
	return(0);
}
