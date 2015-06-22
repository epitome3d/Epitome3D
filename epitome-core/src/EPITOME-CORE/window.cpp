#include "window.h"

namespace EPITOME
{
	GL_Window::GL_Window(int width, int height, char* title)
	{
		//Initialize GLFW
		if (!glfwInit())
		{
			//TODO: Improve error handling
			fprintf(stderr, "GLFW initialization failure.\n");
			return;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
		glfwTerminate();
	}

	GLFWwindow* GL_Window::get_window_handle() const
	{
		return window;
	}
}