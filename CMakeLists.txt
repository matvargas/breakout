# Cmake file 

cmake_minimum_required(VERSION 3.1)

# Set main project name
project(breakout)

# Find packages
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall")

# Include dirs
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIR})

# Add all files to the configuration
file(GLOB breakout_SRC
    "*.h"
    "*.cpp"
)

# Create an executable
add_executable(breakout ${breakout_SRC})

# Add libraries
target_link_libraries(breakout ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
