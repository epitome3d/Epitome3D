#include "window.h"

namespace EPITOME
{
	#if OPENGL
	Window::Window(int width, int height, char* title)
	{
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		
		if (window == NULL)
		{
			//TODO: Improve error handling here as well
			fprintf(stderr, "GLFW window failed.\n");
			glfwTerminate();
			return;
		}
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