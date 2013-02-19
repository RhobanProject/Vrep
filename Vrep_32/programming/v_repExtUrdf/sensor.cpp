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

#include "sensor.h"
#include "commonFunctions.h"
#include "4X4Matrix.h"

sensor::sensor()
{
	//Initialize arrays
	 origin_xyz[0] = 0;   origin_xyz[1] = 0;   origin_xyz[2] = 0;
	 origin_rpy[0] = 0;	  origin_rpy[1] = 0;   origin_rpy[2] = 0;

	 resolution[0]=256;
	 resolution[1]=256;

	 clippingPlanes[0]=0.01f;
	 clippingPlanes[1]=2.0f;

	 cameraSensorPresent=false;
	 proximitySensorPresent=false;
	 gazeboSpec=false;

	 nSensor = -1;
	 nSensorAux = -1;
}


sensor::~sensor()
{
}

