#include "window.h"

namespace EPITOME
{
	GL_Window::GL_Window(int width, int height, char* title)
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

	GL_Window::GL_Window(const GL_Window& win)
	{
		window = win.get_window_handle();
	}

	GL_Window::~GL_Window()
	{
		glfwDestroyWindow(window);
	}

	GLFWwindow* GL_Window::get_window_handle() const
	{
		return window;
	}
}