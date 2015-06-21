cmake_minimum_required(VERSION 3.2)
project(Epitome3D)

option(E3D_ROOT "The root directory of the Epitome3D project.  Can be relative to the output folder." ../)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAPPLE -DUNIX")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DUNIX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNIX")
endif()

if(WIN32)
    set(E3D_LIB_EXTENSION )
    set(E3D_WIN32 WIN32) #prevents console from starting up
else()
    set(E3D_LIB_EXTENSION .lib)
    set(E3D_WIN32 )
endif()

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

#Store location variables
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
set(E3D_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(E3D_BIN ${CMAKE_BINARY_DIR})

#Build GLFW
add_subdirectory(${E3D_SOURCE}/lib/glfw/)
#Build FreeGLUT
add_subdirectory(${E3D_SOURCE}/lib/freeglut/freeglut/freeglut/)

#Link all dependencies
set(E3D_LIBRARIES
    glfw 
    ${GLFW_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    freeglut
    ${FREEGLUT_LIBRARIES}
)

#Include headers
set(E3D_INCLUDES
    epitome-core/src
    include/opengl
    lib/glfw/include
    lib/freeglut/freeglut/freeglut/include
)
include_directories(${E3D_INCLUDES})

add_library(epitome-core STATIC ${E3D_CORE_FILES})

add_executable(epitome-tester ${E3D_WIN32} ${E3D_TESTER_FILES})
target_link_libraries(epitome-tester ${E3D_LIBRARIES})