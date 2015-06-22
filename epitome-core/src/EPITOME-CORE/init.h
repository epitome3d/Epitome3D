#pragma once

#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "system.h"

namespace EPITOME
{
	//Initializes Epitome3D components.
	static void Initialize();

	//Destroys all Epitome3D components and exits with error code SUCCESS.
	static void Exit();

	//Destroys all Epitome3D components and exits with a custom Error instance.
	//Will attempt to send Error to the error function and logger.
	static void Exit(Error errorcode);
}