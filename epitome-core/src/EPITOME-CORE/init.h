#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "system.h"
#include "keyboard.h"
#include "error.h"

namespace EPITOME
{
	//Initializes Epitome3D components.
	void Initialize();

	//Updates the values of all Epitome3D components.
	//This function is to be called at the end of every event loop (frame).
	void Update();

	//Destroys all Epitome3D components and exits with error code SUCCESS.
	void Exit();

	//Destroys all Epitome3D components and exits with a custom Error instance.
	//Will attempt to send Error to the error function and logger.
	void Exit(Error errorcode);
}