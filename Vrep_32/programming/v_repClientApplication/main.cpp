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

#include <QtCore/QCoreApplication>
#include "v_repLib.h"
#include <vector>
#include <QLibrary>
#include <QFileInfo>
#include <QDir>
#include <iostream>

#ifdef Q_WS_WIN
#include <direct.h>
#endif

// Following required to have Lua extension libraries work under Linux. Very strange indeed.
//****************************************************************************
#ifdef LINUX_VREP
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
void dummyFunction()
{
    lua_State *L;
    L=luaL_newstate();
}
#endif
//****************************************************************************

std::vector<int> pluginHandles;
std::string argument1;

void simulatorInit()
{
	std::cout << "Simulator launched.\n";

	QFileInfo pathInfo(QCoreApplication::applicationFilePath());
	std::string pa=pathInfo.path().toStdString();
	QDir dir(pa.c_str());
	dir.setFilter(QDir::Files|QDir::Hidden|QDir::NoSymLinks);
	dir.setSorting(QDir::Name);
	QStringList filters;
	int bnl=8;
#ifdef Q_WS_WIN
	std::string tmp("v_repExt*.dll");
#endif
#ifdef Q_WS_MAC
	std::string tmp("libv_repExt*.dylib");
	bnl=11;
#endif
#ifdef Q_WS_X11
	std::string tmp("libv_repExt*.so");
	bnl=11;
#endif
	filters << tmp.c_str();
	dir.setNameFilters(filters);
	QFileInfoList list=dir.entryInfoList();
	for (int i=0;i<list.size();++i)
	{
		QFileInfo fileInfo=list.at(i);
		std::string bla(fileInfo.baseName().toLocal8Bit());
		std::string tmp;
		if (bnl==bla.size())
			tmp="VrepExt"; // This is the extension module of v_rep (exception in naming)!
		else
			tmp.assign(bla.begin()+bnl,bla.end());

		bool underscoreFound=false;
		for (int i=0;i<int(tmp.length());i++)
		{
			if (tmp[i]=='_')
				underscoreFound=true;
		}
		if (!underscoreFound)
		{
			std::cout << "Plugin '" << tmp.c_str() << "': loading...\n";
			int pluginHandle=simLoadModule(fileInfo.absoluteFilePath().toLocal8Bit().data(),tmp.c_str());
			if (pluginHandle==-3)
#ifdef Q_WS_WIN
				std::cout << "Plugin '" << tmp.c_str() << "': load failed (could not load). The plugin probably couldn't load dependency libraries. Try rebuilding the plugin.\n";
#endif
#ifdef Q_WS_MAC
				std::cout << "Plugin '" << tmp.c_str() << "': load failed (could not load). The plugin probably couldn't load dependency libraries. Try 'otool -L pluginName.dylib' for more infos, or simply rebuild the plugin.\n";
#endif
#ifdef Q_WS_X11
				std::cout << "Plugin '" << tmp.c_str() << "': load failed (could not load). The plugin probably couldn't load dependency libraries. Try 'ldd pluginName.so' for more infos, or simply rebuild the plugin.\n";
#endif
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
	}

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
    std::string libLoc(argv[0]);
    while ((libLoc.length()>0)&&(libLoc[libLoc.length()-1]))
    {
        int l=libLoc.length();
        if (libLoc[l-1]!='/')
            libLoc.erase(libLoc.end()-1);
        else
        { // we might have a 2 byte char:
            if (l>1)
            {
                if (libLoc[l-2]>0x7F)
                    libLoc.erase(libLoc.end()-1);
                else
                    break;

            }
            else
                break;
        }
    }
    chdir(libLoc.c_str());

#ifdef Q_WS_WIN
	LIBRARY lib=loadVrepLibrary("v_rep");
#else
	LIBRARY lib=loadVrepLibrary("libv_rep");
#endif

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
				std::cout << "Failed initializing and running V-REP\n";
			else
				wasRunning=true;
		}
		else
			std::cout << "Error: could not find all required functions in the V-REP library\n";
		unloadVrepLibrary(lib);
	}
	else
		printf("Error: could not find or correctly load the V-REP library\n");
	if (!wasRunning)
		getchar();
	return(0);
}
