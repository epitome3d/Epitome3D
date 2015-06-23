#ifndef EPITOME_GL_WINDOW
#define EPITOME_GL_WINDOW

#include <stdio.h>
#include <stdlib.h>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "error.h"
#include "utility.h"
#include "memory.h"

namespace EPITOME
{
	class Window : public Disposable
	{
	public:
		Window(int width, int height, char* title);
		Window(const Window&);
		Window(Window&&);
		~Window();

		Window& operator=(Window other);
		friend void swap(Window& first, Window& second);

		inline void Dispose() { this->~Window(); }

	#if OPENGL
		GLFWwindow* getWindowHandle() const;
		bool shouldClose() const;
		void swapBuffers();
		void setKeyHandler(GLFWkeyfun func);
		Size<int> getSize() const;
	private:
		GLFWwindow* window;
	};
	#endif
}

#endif