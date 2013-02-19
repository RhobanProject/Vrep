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
#include "bubbleRob.h"

class CBubbleRobContainer
{

public:
	CBubbleRobContainer();
	virtual ~CBubbleRobContainer();


	void removeAll();
	void removeFromID(int theID);
	int insert(CBubbleRob* theBubbleRob);
	CBubbleRob* getFromID(int theID);
	CBubbleRob* getFromAssociatedObject(int theAssociatedObjectID);
	CBubbleRob* getFromIndex(int ind);
	int getCount();

	void actualizeForSceneContent();

	void startOfSimulation();
	void endOfSimulation();
	void handleSimulation();

protected:
	std::vector<CBubbleRob*> _allBubbleRobs; // all CBubbleRobs
};
