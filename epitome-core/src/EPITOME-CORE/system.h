#pragma once

#include <GLFW/glfw3.h>
#include "error.h" //initializes error functions

namespace EPITOME
{
	class System
	{
	public:
		//TODO set window hints here
		//http://www.glfw.org/docs/latest/window.html#window_hints
		//TODO maybe a setSetting() method?
		//TODO add vSync - every single or double VBlank to this (swap interval function)
		//TODO also MSAA

		inline static int exit()
		{
			glfwTerminate();
			return E3D_SUCCESS;
		}
	};
}