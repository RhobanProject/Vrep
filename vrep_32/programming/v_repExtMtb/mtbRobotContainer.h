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

#pragma once

#include <vector>
#include "mtbRobot.h"

class CMtbRobotContainer
{

public:
	CMtbRobotContainer();
	virtual ~CMtbRobotContainer();


	void removeAll();
	void removeFromID(int theID);
	int insert(CMtbRobot* theMtbRobot);
	CMtbRobot* getFromID(int theID);
	CMtbRobot* getFromAssociatedObject(int theAssociatedObjectID);
	CMtbRobot* getFromIndex(int ind);
	int getCount();

	void actualizeForSceneContent();

	void startOfSimulation();
	void endOfSimulation();

protected:
	std::vector<CMtbRobot*> _allMtbRobots; // all CMtbRobots
};
