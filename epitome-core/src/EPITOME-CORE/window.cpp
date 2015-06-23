#include "window.h"

namespace EPITOME
{
	#if OPENGL
	Window::Window(int width, int height, char* title)
	{
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
			Error::Error(E3D_FAIL_CORE_INIT, "glfwCreateWindow() failed", EP_FATAL);

		glfwMakeContextCurrent(window);
	}

	Window::Window(const Window& win)
	{
		window = win.get_window_handle();
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	GLFWwindow* Window::get_window_handle() const
	{
		return window;
	}
	#endif
}