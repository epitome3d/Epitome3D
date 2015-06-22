#include "init.h"

namespace EPITOME
{
	void Initialize()
	{
		//initialize Error class
		Error::ResetErrorFunction();

		//initialize GLFW
		if (!glfwInit())
			Exit(Error(E3D_FAIL_INIT_GLFW, "glfwInit() failed", EP_FATAL));
	}

	void Exit()
	{
		Exit(Error(E3D_SUCCESS, "", EP_RESULT));
	}

	void Exit(Error error)
	{
		System::Exit();
		exit(error.getCode());
	}
}