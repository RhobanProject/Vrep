project (VREPClient)
cmake_minimum_required(VERSION 2.6)

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

