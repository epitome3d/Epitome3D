#ifndef EPITOME_GL_WINDOW
#define EPITOME_GL_WINDOW

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace EPITOME
{
	class GL_Window
	{
	public:
		GL_Window(int width, int height, char* title);
		GL_Window(const GL_Window&);
		~GL_Window();

		GLFWwindow* get_window_handle() const;
	private:
		GLFWwindow* window;
	}
}

#endif