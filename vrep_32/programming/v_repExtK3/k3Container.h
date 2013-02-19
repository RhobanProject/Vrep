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
#include "k3.h"

class CK3Container
{

public:
	CK3Container();
	virtual ~CK3Container();


	void removeAll();
	void removeFromID(int theID);
	int insert(CK3* theK3);
	CK3* getFromID(int theID);
	CK3* getFromAssociatedObject(int theAssociatedObjectID);
	CK3* getFromIndex(int ind);
	int getCount();

	void actualizeForSceneContent();

	void startOfSimulation();
	void endOfSimulation();
	void handleSimulation();
	void scalingEvent();

protected:
	std::vector<CK3*> _allK3s; // all CK3's
};
