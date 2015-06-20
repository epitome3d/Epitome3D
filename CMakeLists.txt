cmake_minimum_required(VERSION 3.2)
project(epitome3d)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#########################################################
# FIND GLUT
#########################################################
#find_package(GLUT REQUIRED)

include_directories(include/opengl)
link_directories(lib/opengl)

include_directories(epitome-core/src)
link_directories(epitome-core/src)

#add_definitions(${GLUT_DEFINITIONS})
#########################################################
# FIND OPENGL
#########################################################
#find_package(OpenGL REQUIRED)
#include_directories(${OpenGL_INCLUDE_DIRS})
#link_directories(${OpenGL_LIBRARY_DIRS})
#add_definitions(${OpenGL_DEFINITIONS})
#########################################################

set(E3D_CORE_FILES
    epitome-core/src/EPITOME-CORE/error.cpp
    epitome-core/src/EPITOME-CORE/error.h
    epitome-core/src/EPITOME-CORE/init.cpp
    epitome-core/src/EPITOME-CORE/init.h
    epitome-core/src/EPITOME-CORE/system.cpp
    epitome-core/src/EPITOME-CORE/system.h
    epitome-core/src/epitome-core.h
    epitome-core/gcc_Debug.h
    epitome-core/gcc_Release.h
)

set(E3D_TESTER_FILES
    epitome-tester/main.cpp
    epitome-tester/gcc_Debug.h
    epitome-tester/gcc_Release.h
)
    
add_library(epitome-core ${E3D_CORE_FILES})
add_executable(epitome-tester ${E3D_TESTER_FILES})

target_link_libraries(epitome-tester ${E3D_LIBRARIES})