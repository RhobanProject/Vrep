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

#include "v_repLib.h"
#include <iostream>
#include <vector>
#include <bitset>
#include "4X4Matrix.h"


class joint
{
public:
	//Variables
	float origin_xyz[3];
	float origin_rpy[3];
	float axis[3];
	float lowerLimit;
	float upperLimit;
	float effortLimitAngular;
	float effortLimitLinear;
	float velocityLimitAngular;
	float velocityLimitLinear;

	C7Vector jointBaseFrame;

	simInt nJoint;
	std::string name;
	simInt jointType;

	std::string parentJoint;
	std::string parentLink;
	std::string childLink;

	//Functions
	joint(void);
	~joint(void);
	
	//Read
	void setJointType(std::string gazeboJointType);
	void setOrigin(std::string gazebo_origin_xyz,std::string gazebo_origin_rpy);
	void setAxis(std::string gazebo_axis_xyz);
	void setParent(std::string gazebo_parentName);
	void setChild(std::string gazebo_childName);
};

