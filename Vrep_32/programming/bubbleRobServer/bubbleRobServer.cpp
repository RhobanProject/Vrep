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

#include <stdio.h>
#include "simpleInConnection.h"
#include <cstdlib>
#define pi 3.141593f

int main(int argc, char* argv[])
{ // We connect to the port number passed as argument
	int portNb=0;
	if (argv[1]!=NULL)
		portNb=atoi(argv[1]);
	if (portNb==0)
	{
		printf("Indicate the connection port number as argument!\n",portNb);
		Sleep(5000);
		return 0;
	}

	CSimpleInConnection connection(portNb);
	printf("Connecting to client...\n");
	if (connection.connectToClient())
	{
		printf("Connected with client.\n");
		float driveBackStartTime=-99.0f;
		float motorSpeeds[2];
		while (true)
		{ // This is the server loop (the robot's control loop):
			int receivedDataLength;
			char* receivedData=connection.receiveData(receivedDataLength);
			if (receivedData!=NULL)
			{ // We received data. The server ALWAYS replies!
				// We received 2 floats (the sensorDistance and the simulation time):
				float sensorReading=((float*)receivedData)[0];
				float simulationTime=((float*)receivedData)[1];
				delete[] receivedData;

				// We have a very simple control: when we detected something, we simply drive back while slightly turning for 3 seconds
				// If we didn't detect anything, we drive forward:
				if (simulationTime-driveBackStartTime<3.0f)
				{ // driving backwards while slightly turning:
					motorSpeeds[0]=-pi*0.5f;
					motorSpeeds[1]=-pi*0.25f;
				}
				else
				{ // going forward:
					motorSpeeds[0]=pi;
					motorSpeeds[1]=pi;
					if (sensorReading>0.0f)
						driveBackStartTime=simulationTime; // We detected something, and start the backward mode
				}

				// We reply with 2 floats (the left and right motor speed in rad/sec)
				if (!connection.replyToReceivedData((char*)motorSpeeds,sizeof(float)*2))
				{
					printf("Failed to send reply.\n");
					break;
				}
			}
			else
				break; // error
		}
	}
	else
		printf("Failed to connect to client.\n");
	Sleep(5000);
	return 0;
}

