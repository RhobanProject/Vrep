project (VREPClient)
cmake_minimum_required(VERSION 2.6)

set (VREP_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/../")

set (VREP_PATH
    "${VREP_ROOT}/Vrep_32/programming/"
    CACHE "The VRep build path" STRING)

set (CLIENT_PATH
    "${VREP_ROOT}/Client")

set (CLIENT_SOURCES
    ${CLIENT_PATH}/VREPClient.cpp
    ${CLIENT_PATH}/Motor.cpp
    ${CLIENT_PATH}/Object.cpp
    ${CLIENT_PATH}/ForceSensor.cpp
    )

include_directories(${CLIENT_PATH})

set (SOURCES main.cpp)

set (EXTRA_LIBRARIES pthread :remoteApi.so)

include_directories (${VREP_PATH}/remoteApi ${VREP_PATH}/include)
link_directories (${VREP_PATH}/remoteApiSharedLib)
add_definitions (-DNON_MATLAB_PARSING)

add_executable (VREPClient ${SOURCES} ${CLIENT_SOURCES})
target_link_libraries (VREPClient ${EXTRA_LIBRARIES})
