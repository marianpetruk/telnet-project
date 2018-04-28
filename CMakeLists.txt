cmake_minimum_required(VERSION 3.5)
project(echoserver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE OFF)


find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})


FILE(GLOB_RECURSE MYSHELL_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.h")

add_executable(shellserver
        Server.cpp Server.h
        Session.cpp Session.h
        ${MYSHELL_FILES})
target_include_directories(shellserver PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(shellserver ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(echouser echouser.cpp)
target_include_directories(echouser PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(echouser ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})