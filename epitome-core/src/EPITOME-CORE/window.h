#ifndef EPITOME_GL_WINDOW
#define EPITOME_GL_WINDOW

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "error.h"
#include "utility.h"

namespace EPITOME
{
	class Window
	{
	public:
		Window(int width, int height, char* title);
		Window(const Window&);
		~Window();

	#if OPENGL
		GLFWwindow* get_window_handle() const;
		void set_key_handler(GLFWkeyfun func);
		size<int> get_size() const;
	private:
		GLFWwindow* window;
	};
	#endif
}

#endif