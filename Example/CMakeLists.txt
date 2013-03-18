project (Client)
cmake_minimum_required(VERSION 2.6)

set (VREP_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/../"
    CACHE "VRep root dir" STRING)

set (VREP_PATH
    "${VREP_ROOT}/Vrep_32/programming/"
    CACHE "The VRep build path" STRING)

set (CLIENT_PATH
    "${VREP_ROOT}/Client")

add_subdirectory (${CLIENT_PATH} client)
include_directories (${CLIENT_PATH})

set (SOURCES main.cpp)

set (EXTRA_LIBRARIES pthread :remoteApi.so VREPClient)

execute_process (COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/genscript.sh"
                "${VREP_ROOT}" "${CMAKE_BINARY_DIR}/vrep")

include_directories (${VREP_PATH}/remoteApi ${VREP_PATH}/include)
link_directories (${VREP_PATH}/remoteApiSharedLib)
add_definitions (-DNON_MATLAB_PARSING)

add_executable (Client ${SOURCES} ${CLIENT_SOURCES})
target_link_libraries (Client ${EXTRA_LIBRARIES})
