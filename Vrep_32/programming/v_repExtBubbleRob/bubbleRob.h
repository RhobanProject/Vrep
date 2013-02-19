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

class CBubbleRob
{
public:
	CBubbleRob();
	virtual ~CBubbleRob();

	void setID(int newID);
	int getID();
	void setAssociatedObject(int objID,int objUniqueID);
	int getAssociatedObject();
	int getAssociatedObjectUniqueId();

	// Following 4 needed to keep a scene object's custom data synchronized with CBubbleRob's data (_maxVelocity, which is stored inside a scene object)
	void synchronizeSceneObject();
	void synchronize();
	static void putBubbleRobTagToSceneObject(int objectHandle,float maxVelocity);

	void setMaxVelocity(float maxVel);
	float getMaxVelocity();

	// Following 5 are called (indirectly) from a Lua-script:
	void startOfSimulation();
	bool endOfSimulation();
	void handleSimulation();
	void moveAndAvoid(float duration,float backRelativeVelocities[2],char* setToZeroAtMovementEnd);
	void stop();

protected:
	void _initialize();
	
	int _id;						// to identify individual CBubbleRobs
	int _associatedObjectUniqueID;	// the unique ID of the scene object associated with this CBubbleRob
	int _associatedObjectID;		// the handle of the scene object associated with this CBubbleRob
	float _maxVelocity;				// the max velocity of BubbleRob. This value has to be synchronized with the BUBBLEROB_DATA_MAXVELOCITY tag

	bool _initialized;					// Whether following values are initialized:					
	int _handleOfLeftJoint;				// Object handle corresponding to BubbleRob's left motor
	int _handleOfRightJoint;			// Object handle corresponding to BubbleRob's right motor
	int _handleOfProximitySensor;		// Object handle corresponding to BubbleRob's proximity sensor
	float _movementDuration;			// The duration of the "moveAndAvoid" sequence
	float _backMovementDuration;		// The duration of a "back" sequence
	float _backRelativeVelocities[2];	// The motor relative velocities for the "back" movement
	char* _setToZeroAtMovementEnd;		// Used when the simExtBubbleMoveAndAvoid command waits until movement duration is zero
};
