cmake_minimum_required(VERSION 3.6)
project(OCB)
find_package(Boost COMPONENTS system filesystem thread date_time REQUIRED)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

#Possible builds VALIDATOR_DEBUG & VALIDATOR_RELEASE or GENERATOR (include tests)

set(BUILD_CONFIGURATION "VALIDATOR_DEBUG")

IF(${BUILD_CONFIGURATION} MATCHES "VALIDATOR_DEBUG")
    set(CMAKE_BUILD_TYPE "DEBUG")
        #extends mode
    add_definitions(-DVALIDATOR)
ENDIF(${BUILD_CONFIGURATION} MATCHES "VALIDATOR_DEBUG")

IF(${BUILD_CONFIGURATION} MATCHES "VALIDATOR_RELEASE")
    set(CMAKE_BUILD_TYPE "RELEASE")
    #extends mode
    add_definitions(-DVALIDATOR)
ENDIF(${BUILD_CONFIGURATION} MATCHES "VALIDATOR_RELEASE")

IF(${BUILD_CONFIGURATION} MATCHES "GENERATOR")
    set(CMAKE_BUILD_TYPE "DEBUG")
    add_definitions(-DGENERATOR)
ENDIF(${BUILD_CONFIGURATION} MATCHES "GENERATOR")

add_subdirectory(crypto)
add_subdirectory(src)

set(SOURCE_FILES core.cpp)

add_executable(OCB ${SOURCE_FILES})

target_link_libraries(OCB lamport Boost::thread -lsodium -lboost_system -lboost_filesystem)
