cmake_minimum_required(VERSION 3.5)
project(echoserver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE OFF)


find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})


FILE(GLOB_RECURSE SERVER_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/server/*.h")

add_executable(shellserver runserver.cpp ${SERVER_FILES})
target_include_directories(shellserver PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(shellserver ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(shelluser shelluser.cpp)
target_include_directories(shelluser PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(shelluser ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})