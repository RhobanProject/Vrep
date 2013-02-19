// This file is part of the URDF PLUGIN for V-REP
//  
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// A big thanks to Ignacio Tartavull for his precious help!
// 
// The URDF PLUGIN is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The URDF PLUGIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// The URDF PLUGIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the URDF PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------

//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

// The URDF plugin is courtesy of Ignacio Tartavull. A few modifications by Marc.

#pragma once

#include "commonFunctions.h"
#include <string>
#include "v_repLib.h"

void printToConsole(const char* txt)
{
	static int handle=-1;
	std::string text(txt);
	text+="\n";
	std::cout << text;
	if (simAuxiliaryConsolePrint(handle,text.c_str())<=0)
	{
		handle=simAuxiliaryConsoleOpen("URDF import",5000,2+4,NULL,NULL,NULL,NULL);
		simAuxiliaryConsolePrint(handle,text.c_str());
	}
}

void stringToArray(float array[],const std::string xyz)
{
	
	std::string buf; 
    std::stringstream ss(xyz); 

   	int i = 0;
	while (ss >> buf){ array[i++]=getFloat(buf);}
	
	
}

float getFloat(const std::string& text)
{
	try
	{
		return(boost::lexical_cast<float>(text));
	}
	catch (boost::bad_lexical_cast &)
	{
		return(0.0f);
	}
}

int getInt(const std::string& text)
{
	try
	{
		return(boost::lexical_cast<int>(text));
	}
	catch (boost::bad_lexical_cast &)
	{
		return(0);
	}
}


bool isArrayEmpty(float array[])
{
	if(array[0] == 0.0f && array[1] ==0.0f && array[2] == 0.0f){ return true;}
	else {return false;}
}
float* minus(float arr[])
{
	arr[0] = -arr[0];
	arr[1] = -arr[1];
	arr[2] = -arr[2];

	return arr;
}
std::string printMatrix(const float arr[])
{
	return (" value0 = "+boost::lexical_cast<std::string>(arr[0])+" value1 = "+boost::lexical_cast<std::string>(arr[1])+ " value2 = "+boost::lexical_cast<std::string>(arr[2])).c_str();
}

