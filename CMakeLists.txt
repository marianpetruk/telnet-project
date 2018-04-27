cmake_minimum_required(VERSION 3.5)
project(echoserver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE OFF)


find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(echoserver Server.cpp execute.cpp execute.h)
target_include_directories(echoserver PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(echoserver ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(echouser echouser.cpp)
target_include_directories(echouser PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(echouser ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})



add_executable(oldechoserver echoserver.cpp)
target_include_directories(echoserver PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(echoserver ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})