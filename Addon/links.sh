#!/bin/bash

#Argument $1 is the Vrep root path

ln -fs $1/Addon/remoteApiConnections.txt $1/Vrep/remoteApiConnections.txt
ln -fs $1/Addon/extApiCustomConst.h $1/Vrep/programming/include/extApiCustomConst.h
ln -fs $1/Addon/extApiCustom.c $1/Vrep/programming/remoteApi/extApiCustom.c
ln -fs $1/Addon/extApiCustom.h $1/Vrep/programming/remoteApi/extApiCustom.h
ln -fs $1/Addon/simxCustomCmd.cpp $1/Vrep/programming/v_repExtRemoteApi/simxCustomCmd.cpp

