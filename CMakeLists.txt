cmake_minimum_required(VERSION 3.10)

# Set the project name
project(bad-pixel-detection CXX)

# Set the path to the OpenCV installation.
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/lib/opencv")

# Find the OpenCV library
FIND_PACKAGE(OpenCV REQUIRED)

# Add the include directory for FFmpeg and OpenCV
include_directories(SYSTEM ${OpenCV_INCLUDE_DIR})

# Add the path to the FFmpeg and OpenCV libraries
link_directories("${CMAKE_SOURCE_DIR}/lib/opencv/build/x64/vc16/lib")

add_executable(${PROJECT_NAME} src/main.cpp)

# Link against the FFmpeg and OpenCV libraries for each executable
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
