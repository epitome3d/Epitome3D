#include "keyboard.h"

namespace EPITOME
{
	void Keyboard::Initialize()
	{
		
	}

	void Keyboard::AddWindow(Window* window)
	{
		GLFWkeyfun fn = glfwSetKeyCallback(window->getWindowHandle(), GLFWKeyFunction);
		if (!fn)
			Error(E3D_FAIL_CORE_INIT, "glfwSetKeyCallback() failed");
	}

	void Keyboard::RemoveWindow(Window * window)
	{
		glfwSetKeyCallback(window->getWindowHandle(), NULL);
	}

	void Keyboard::GLFWKeyFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		
	}
}