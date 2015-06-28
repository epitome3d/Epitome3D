cmake_minimum_required(VERSION 3.2)
project(Epitome3D)

#option(E3D_ROOT "The root directory of the Epitome3D project.  Can be relative to the output folder." ../)

#set OpenGL as the renderer for now
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOPENGL")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAC -DUNIX")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DUNIX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNKNOWN")
endif()

if(WIN32)
    set(E3D_WIN32 WIN32) #prevents console from starting up
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(E3D_WIN32 )
endif()

set(E3D_CORE_FILES
    epitome-core/src/EPITOME-CORE/display.cpp
    epitome-core/src/EPITOME-CORE/display.h
    epitome-core/src/EPITOME-CORE/error.cpp
    epitome-core/src/EPITOME-CORE/error.h
    epitome-core/src/EPITOME-CORE/init.cpp
    epitome-core/src/EPITOME-CORE/init.h
    epitome-core/src/EPITOME-CORE/keyboard.cpp
    epitome-core/src/EPITOME-CORE/keyboard.h
    epitome-core/src/EPITOME-CORE/keys.h
    epitome-core/src/EPITOME-CORE/mouse.cpp
    epitome-core/src/EPITOME-CORE/mouse.h
    epitome-core/src/EPITOME-CORE/memory.cpp
    epitome-core/src/EPITOME-CORE/memory.h
    epitome-core/src/EPITOME-CORE/system.cpp
    epitome-core/src/EPITOME-CORE/system.h
    epitome-core/src/EPITOME-CORE/window.cpp
    epitome-core/src/EPITOME-CORE/window.h
    epitome-core/src/EPITOME-CORE/utils.h
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
set(E3D_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(E3D_BIN ${CMAKE_BINARY_DIR})

#Build GLFW
add_subdirectory(${E3D_SOURCE}/lib/glfw/)
#Build FreeGLUT
add_subdirectory(${E3D_SOURCE}/lib/freeglut/freeglut/freeglut/)

#Add Epitome Core
add_library(epitome-core STATIC ${E3D_CORE_FILES})

#Link all dependencies
set(E3D_LIBRARIES
    glfw 
    ${GLFW_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    freeglut
    ${FREEGLUT_LIBRARIES}
    epitome-core
)

#Include headers
set(E3D_INCLUDES
    epitome-core/src
    include/opengl
    lib/glfw/include
    lib/freeglut/freeglut/freeglut/include
)
include_directories(${E3D_INCLUDES})

#Add Epitome Tester
add_executable(epitome-tester ${E3D_WIN32} ${E3D_TESTER_FILES})
target_link_libraries(epitome-tester ${E3D_LIBRARIES})

#Set folders for Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(uninstall PROPERTIES FOLDER "CMakePredefinedTargets")

MACRO(FREEGLUT_ADD name)
    IF(FREEGLUT_BUILD_DEMOS)
        IF(FREEGLUT_BUILD_SHARED_LIBS)
            set_target_properties(${name} PROPERTIES FOLDER "FreeGLUT/Demos")
        ENDIF()
        IF(FREEGLUT_BUILD_STATIC_LIBS)
            set_target_properties(${name}_static PROPERTIES FOLDER "FreeGLUT/Demos")
        ENDIF()
    ENDIF()
ENDMACRO()

IF(FREEGLUT_BUILD_SHARED_LIBS)
    set_target_properties(freeglut PROPERTIES FOLDER "FreeGLUT")
endif()
IF(FREEGLUT_BUILD_STATIC_LIBS)
    set_target_properties(freeglut_static PROPERTIES FOLDER "FreeGLUT")
endif()
FREEGLUT_ADD(CallbackMaker)
FREEGLUT_ADD(Fractals)
FREEGLUT_ADD(Fractals_random)
FREEGLUT_ADD(Lorenz)
FREEGLUT_ADD(One)
FREEGLUT_ADD(Resizer)
FREEGLUT_ADD(multi-touch)
FREEGLUT_ADD(shapes)
FREEGLUT_ADD(smooth_opengl3)
FREEGLUT_ADD(subwin)
FREEGLUT_ADD(timer)
if(LINUX)
    FREEGLUT_ADD(spaceball)
endif()

