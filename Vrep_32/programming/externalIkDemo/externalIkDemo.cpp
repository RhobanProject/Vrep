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

#include "extIk.h"
#include <stdio.h>
#include <stdlib.h>

extern "C" {
    #include "extApi.h"
}

int main(int argc, char* argv[])
{
	int portNb=0;
	char* motorSignalNames[3];
	if (argc>=5)
	{
		portNb=atoi(argv[1]);
		motorSignalNames[0]=argv[2];
		motorSignalNames[1]=argv[3];
		motorSignalNames[2]=argv[4];
	}
	else
	{
		printf("Indicate following arguments: 'portNumber motor1SignalName motor2SignalName motor3SignalName'!\n");
		extApi_sleepMs(5000);
		return 0;
	}

	FILE *file;
	file=fopen("irb360.ik","rb");
	unsigned char* data=NULL;
	int dataLength=0;
	if (file)
	{
		fseek(file,0,SEEK_END);
		unsigned long fl=ftell(file);
		dataLength=(int)fl;
		fseek(file,0,SEEK_SET);
		data=new unsigned char[dataLength];
		fread((char*)data,dataLength,1,file);
		fclose(file);
	}
	else
	{
		printf("The kinematic content file 'irb360.ik' could not be read!\n");
		extApi_sleepMs(5000);
		return 0;
	}

	if (simxStart("127.0.0.1",portNb,true,true,2000)!=-1)
	{
		// Initialize the embedded robot model:
		simEmbLaunch();
		int objectCount=simEmbStart(data,dataLength);
		int embeddedModelMotorHandles[3];
		int embeddedModelIkLinMotorHandles[3];
		embeddedModelMotorHandles[0]=simEmbGetObjectHandle("irb360_drivingJoint1");
		embeddedModelMotorHandles[1]=simEmbGetObjectHandle("irb360_drivingJoint2");
		embeddedModelMotorHandles[2]=simEmbGetObjectHandle("irb360_drivingJoint3");
		embeddedModelIkLinMotorHandles[0]=simEmbGetObjectHandle("irb360_cartesianX");
		embeddedModelIkLinMotorHandles[1]=simEmbGetObjectHandle("irb360_cartesianY");
		embeddedModelIkLinMotorHandles[2]=simEmbGetObjectHandle("irb360_cartesianZ");
		float embeddedModelMotorPositions[3];
		float v=0.0f;
		float a=0.0f;
		while (simxGetConnectionId()!=-1)
		{
			// Set the desired tip position:
			float x=sin(v)*0.5f;
			float y=cos(v)*0.5f;
			float z=sin(v*3.0f)*0.1f;
			simEmbSetJointPosition(embeddedModelIkLinMotorHandles[0],x*a*1.1f);
			simEmbSetJointPosition(embeddedModelIkLinMotorHandles[1],y*a*1.1f);
			simEmbSetJointPosition(embeddedModelIkLinMotorHandles[2],z*(1.0f-a));
			// calculate IK:
			simEmbHandleIkGroup(sim_handle_all);
			// Read the corresponding motor angles:
			simEmbGetJointPosition(embeddedModelMotorHandles[0],embeddedModelMotorPositions);
			simEmbGetJointPosition(embeddedModelMotorHandles[1],embeddedModelMotorPositions+1);
			simEmbGetJointPosition(embeddedModelMotorHandles[2],embeddedModelMotorPositions+2);
			// Stream motor angles:
			simxPauseCommunication(1); // this guarantees that following 3 values will arrive at the same time!
			simxSetFloatSignal(motorSignalNames[0],embeddedModelMotorPositions[0],simx_opmode_oneshot);
			simxSetFloatSignal(motorSignalNames[1],embeddedModelMotorPositions[1],simx_opmode_oneshot);
			simxSetFloatSignal(motorSignalNames[2],embeddedModelMotorPositions[2],simx_opmode_oneshot);
			simxPauseCommunication(0); // never forget to 'unpause' it!
		
			v=v+0.04f;
			if (v>10.0f)
			{
				a=a+0.0005f;
				if (a>1.0f)
					a=1.0f;
			}
			extApi_sleepMs(5);
		}
		simEmbShutDown();
		simxFinish();
	}
	return(0);
}

