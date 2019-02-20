cmake_minimum_required(VERSION 3.13)
project(SCRIPT)
find_package(Boost COMPONENTS system filesystem thread date_time REQUIRED)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)

add_executable(SCRIPT script.cpp )
target_link_libraries(SCRIPT Boost::thread -lboost_system -lboost_filesystem)