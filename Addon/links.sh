#!/bin/bash

#Argument $1 is the Vrep root path
VREP_ROOT="$1"

ln -fs $VREP_ROOT/Addon/remoteApiConnections.txt $VREP_ROOT/Vrep/remoteApiConnections.txt
ln -fs $VREP_ROOT/Addon/extApiCustomConst.h $VREP_ROOT/Vrep/programming/include/extApiCustomConst.h
ln -fs $VREP_ROOT/Addon/extApiCustom.c $VREP_ROOT/Vrep/programming/remoteApi/extApiCustom.c
ln -fs $VREP_ROOT/Addon/extApiCustom.h $VREP_ROOT/Vrep/programming/remoteApi/extApiCustom.h
ln -fs $VREP_ROOT/Addon/simxCustomCmd.cpp $VREP_ROOT/Vrep/programming/v_repExtRemoteApi/simxCustomCmd.cpp

ln -fs $VREP_ROOT/Addon/link.cpp $VREP_ROOT/Vrep/programming/v_repExtUrdf/link.cpp
ln -fs $VREP_ROOT/Addon/link.h $VREP_ROOT/Vrep/programming/v_repExtUrdf/link.h
ln -fs $VREP_ROOT/Addon/robot.cpp $VREP_ROOT/Vrep/programming/v_repExtUrdf/robot.cpp
ln -fs $VREP_ROOT/Addon/robot.h $VREP_ROOT/Vrep/programming/v_repExtUrdf/robot.h
