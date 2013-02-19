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

// Make sure to have the server side running in V-REP!
// Start the server from a child script with following command:
// simExtRemoteApiStart(portNumber) -- starts a remote API server service on the specified port

#include <stdio.h>
#include <stdlib.h>

extern "C" {
    #include "extApi.h"
/*	#include "extApiCustom.h" if you wanna use custom remote API functions! */
}

int main(int argc,char* argv[])
{
	int portNb=0;
	int leftMotorHandle;
	int rightMotorHandle;
	int sensorHandle;
	if (argc>=5)
	{
		portNb=atoi(argv[1]);
		leftMotorHandle=atoi(argv[2]);
		rightMotorHandle=atoi(argv[3]);
		sensorHandle=atoi(argv[4]);
	}
	else
	{
		printf("Indicate following arguments: 'portNumber leftMotorHandle rightMotorHandle sensorHandle'!\n");
		extApi_sleepMs(5000);
		return 0;
	}
	if (simxStart("127.0.0.1",portNb,true,true,2000)!=-1)
	{
		int driveBackStartTime=-99000;
		float motorSpeeds[2];
		while (simxGetConnectionId()!=-1)
		{
			char sensorTrigger=0;
			if (simxReadProximitySensor(sensorHandle,&sensorTrigger,NULL,NULL,NULL,simx_opmode_continuous)==simx_error_noerror)
			{ // We succeeded at reading the proximity sensor
				int simulationTime=simxGetLastCmdTime();
				if (simulationTime-driveBackStartTime<3000)
				{ // driving backwards while slightly turning:
					motorSpeeds[0]=-3.1415f*0.5f;
					motorSpeeds[1]=-3.1415f*0.25f;
				}
				else
				{ // going forward:
					motorSpeeds[0]=3.1415f;
					motorSpeeds[1]=3.1415f;
					if (sensorTrigger)
						driveBackStartTime=simulationTime; // We detected something, and start the backward mode
				}
				simxSetJointTargetVelocity(leftMotorHandle,motorSpeeds[0],simx_opmode_oneshot);			
				simxSetJointTargetVelocity(rightMotorHandle,motorSpeeds[1],simx_opmode_oneshot);			
			}
			extApi_sleepMs(5);
		}
		simxFinish();
	}
	return(0);
}

