#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "system.h"
#include "keyboard.h"

namespace EPITOME
{
	//Initializes Epitome3D components.
	void Initialize();

	//Destroys all Epitome3D components and exits with error code SUCCESS.
	void Exit();

	//Destroys all Epitome3D components and exits with a custom Error instance.
	//Will attempt to send Error to the error function and logger.
	void Exit(Error errorcode);
}