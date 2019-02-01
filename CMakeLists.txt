cmake_minimum_required(VERSION 3.6)
project(OCB)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#Possible builds VALIDATOR or GENERATOR (in future will include tests)

set(BUILD_CONFIGURATION "VALIDATOR")

IF(${BUILD_CONFIGURATION} MATCHES "VALIDATOR")
    set(CMAKE_BUILD_TYPE "VALIDATOR")
    add_definitions(-DVALIDATOR)
ENDIF(${BUILD_CONFIGURATION} MATCHES "VALIDATOR")

IF(${BUILD_CONFIGURATION} MATCHES "GENERATOR")
    set(CMAKE_BUILD_TYPE "GENERATOR")
    add_definitions(-DGENERATOR)
ENDIF(${BUILD_CONFIGURATION} MATCHES "GENERATOR")

add_subdirectory(crypto)
add_subdirectory(source)

set(SOURCE_FILES core.cpp)

add_executable(OCB ${SOURCE_FILES})

target_link_libraries(OCB lamport -lsodium)