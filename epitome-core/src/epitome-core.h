#pragma once

#ifdef _WINDOWS
#define WINDOWS
#endif

#ifdef __gnu_linux__
#define LINUX
#endif

#include "EPITOME-CORE/init.cpp" //functions to initialize Epitome3D
#include "EPITOME-CORE/error.h" //initializes error functions
#include "EPITOME-CORE/system.h" //initializes system specifications