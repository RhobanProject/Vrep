#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

extern "C" {
    #include "extApi.h"
}

void checkError(simxInt error)
{
    if (error != simx_error_noerror) {
        std::cerr << "Error " << error << std::endl;
        simxInt nbError;
        char* strError;
        simxGetLastErrors(&nbError, &strError, simx_opmode_oneshot_wait);
        std::cout << nbError << std::endl;
        for (int i=nbError;i>0;i--) {
            std::cerr << strError << std::endl;
        }
        simxFinish();
        exit(-1);
    }
}

int amain(int argc,char* argv[])
{
    //Network configuration
    int port = 4242;
    char ip[] = "127.0.0.1";
    //Connection
    if (simxStart(ip, port, true, true, 2000) != -1) {
        std::cout << "Connection success" << std::endl;
        simxInt error;
        //Retrieve servos handle
        simxInt servosArm[5];
        simxInt servosFoot[5];
        error = simxGetObjectHandle("JointBras1", &(servosArm[0]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointBras2", &(servosArm[1]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointBras3", &(servosArm[2]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointBras4", &(servosArm[3]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointBras5", &(servosArm[4]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointPied1", &(servosFoot[0]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointPied2", &(servosFoot[1]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointPied3", &(servosFoot[2]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointPied4", &(servosFoot[3]), simx_opmode_oneshot_wait);
            checkError(error);
        error = simxGetObjectHandle("JointPied5", &(servosFoot[4]), simx_opmode_oneshot_wait);
            checkError(error);
        //Configuring servos
        double t = 0;
        while (t < 60.0) {
            for (int i=0;i<5;i++) {
                double pos = 0.5*sin(t+i*t);
                error = simxSetJointTargetPosition(servosArm[i], pos, simx_opmode_oneshot);
            }
            for (int i=0;i<5;i++) {
                double pos = 0.3*sin(t+i*t);
                error = simxSetJointTargetPosition(servosFoot[i], pos, simx_opmode_oneshot);
            }
            usleep(20000);
            t += 0.02;
        }
        //Close connection
        simxFinish();
    } else {
        std::cerr << "Unable to connect to V-REP server" << std::endl;
    }

    return(0);
}

