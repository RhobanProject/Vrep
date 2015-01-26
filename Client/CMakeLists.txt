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
execute_process (COMMAND "/bin/bash" "-c" "cd ${VREP_ROOT}/Vrep/programming/v_repExtRemoteApi; make -f makefile")
execute_process (COMMAND "/bin/bash" "-c" "cp ${VREP_ROOT}/Vrep/programming/v_repExtRemoteApi/lib/libv_repExtRemoteApi.so ${VREP_ROOT}/Vrep/")
execute_process (COMMAND "/bin/bash" "-c" "cd ${VREP_ROOT}/Vrep/programming/v_repExtUrdf; qmake v_repExtUrdf.pro; make")
execute_process (COMMAND "/bin/bash" "-c" "cp ${VREP_ROOT}/Vrep/programming/v_repExtUrdf/libv_repExtUrdf.so ${VREP_ROOT}/Vrep/")

set (VREP_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/../Vrep/programming/"
    CACHE "The VRep build path" STRING)

set (SOURCES VREPClient.cpp Motor.cpp Object.cpp ForceSensor.cpp 
    ${VREP_ROOT}/Vrep/programming/remoteApi/extApi.c
    ${VREP_ROOT}/Vrep/programming/remoteApi/extApiCustom.c
    ${VREP_ROOT}/Vrep/programming/remoteApi/extApiPlatform.c)

set (EXTRA_LIBRARIES pthread)

include_directories (${VREP_PATH}/remoteApi ${VREP_PATH}/include)
add_definitions (-DNON_MATLAB_PARSING)
add_definitions (-DMAX_EXT_API_CONNECTIONS=255)

add_library (VREPClient SHARED ${SOURCES})
target_link_libraries (VREPClient ${EXTRA_LIBRARIES})

