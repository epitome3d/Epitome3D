#include "init.h"

namespace EPITOME
{
	void initialize()
	{
		//initialize Error class
		Error::resetErrorFunction();

		//initialize GLFW
		if (!glfwInit())
			exit(Error(E3D_FAIL_CORE_INIT, "glfwInit() failed", EP_FATAL));
	}

	void update()
	{
		glfwPollEvents();
	}

	void exit()
	{
		exit(Error(E3D_SUCCESS, "", EP_RESULT));
	}

	void exit(Error error)
	{
		System::exit();
		exit(error.getCode());
	}
}