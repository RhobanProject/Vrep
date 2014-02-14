project (VREPClient)
cmake_minimum_required(VERSION 2.6)

set (VREP_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/../"
    CACHE "VRep root dir" STRING)

execute_process (COMMAND "/bin/bash" "-c" "cd ${VREP_ROOT}; echo -n `pwd`"
               OUTPUT_VARIABLE VREP_ROOT)

#Create symbolic links from Addon to Vrep directory
execute_process (COMMAND "/bin/bash" "-c" "cd ${VREP_ROOT}; Addon/links.sh ${VREP_ROOT}")

#Recompile Vrep parts which are overloaded by our implementation
execute_process (COMMAND "/bin/bash" "-c" "cd ${VREP_ROOT}/Vrep_32/programming; make -f remoteApiSharedLib_Makefile")
execute_process (COMMAND "/bin/bash" "-c" "cd ${VREP_ROOT}/Vrep_32/programming; make -f v_repExtRemoteApi_Makefile")
execute_process (COMMAND "/bin/bash" "-c" "mv ${VREP_ROOT}/Vrep_32/programming/libv_repExtRemoteApi.so ${VREP_ROOT}/Vrep_32/")

set (VREP_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/../Vrep_32/programming/"
    CACHE "The VRep build path" STRING)

set (SOURCES VREPClient.cpp Motor.cpp Object.cpp ForceSensor.cpp)

set (EXTRA_LIBRARIES pthread :remoteApi.so)

include_directories (${VREP_PATH}/remoteApi ${VREP_PATH}/include)
link_directories (${VREP_PATH}/remoteApiSharedLib)
add_definitions (-DNON_MATLAB_PARSING)

add_library (VREPClient SHARED ${SOURCES})
target_link_libraries (VREPClient ${EXTRA_LIBRARIES})

