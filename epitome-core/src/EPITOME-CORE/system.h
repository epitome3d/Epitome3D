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
			EPITOME::Errors::CreateError(0, "");
			return true;
		}
	};
}