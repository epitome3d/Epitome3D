cmake_minimum_required(VERSION 3.2)
project(epitome-core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#########################################################
# FIND GLUT
#########################################################
#find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
include_directories("../epitome-core/src")
link_directories("../epitome-core/src")
#add_definitions(${GLUT_DEFINITIONS})
#########################################################
# FIND OPENGL
#########################################################
#find_package(OpenGL REQUIRED)
#include_directories(${OpenGL_INCLUDE_DIRS})
#link_directories(${OpenGL_LIBRARY_DIRS})
#add_definitions(${OpenGL_DEFINITIONS})
#########################################################

set(SOURCE_FILES
    main.cpp
    gcc_Debug.h
    gcc_Release.h)

add_executable(Epitome3D ${SOURCE_FILES})

target_link_libraries(Epitome3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )