cmake_minimum_required(VERSION 3.11)
project(mergeImage)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(mergeImage main.cpp)

target_link_libraries(mergeImage ${OpenCV_LIBS})