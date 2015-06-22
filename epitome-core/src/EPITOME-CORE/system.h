#pragma once

#include <GLFW/glfw3.h>
#include "error.h" //initializes error functions

namespace EPITOME
{
	class System
	{
	public:
		inline static int Exit()
		{
			glfwTerminate();
			return E3D_SUCCESS;
		}
	};
}