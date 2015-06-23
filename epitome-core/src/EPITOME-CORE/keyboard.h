#pragma once

#include "utils.h"
#include "window.h"
#include "keys.h"
#include <GLFW/glfw3.h>

namespace EPITOME
{
	//static void(*_E3D_keyCallbackFn)(GLFWwindow*, int, int, int, int);

	class Window; //forward declaration of Window to solve circular reference issues
	class Keyboard
	{
	public:
		//Add a window to the key manager
		static void AddWindow(Window* window);

		//interal key function
		static void GLFWKeyFunction(GLFWwindow*, int, int, int, int);
	private:

	};
}