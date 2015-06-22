#ifndef EPITOME_GL_WINDOW
#define EPITOME_GL_WINDOW

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace EPITOME
{
	class Window
	{
	#if OPENGL
	public:
		Window(int width, int height, char* title);
		Window(const Window&);
		~Window();
		
		GLFWwindow* get_window_handle() const;
	private:
		GLFWwindow* window;
	}
	#endif
}

#endif