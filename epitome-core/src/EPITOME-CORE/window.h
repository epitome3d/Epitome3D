#ifndef EPITOME_GL_WINDOW
#define EPITOME_GL_WINDOW

#include <stdio.h>
#include <stdlib.h>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "error.h"
#include "utils.h"
#include "memory.h"
#include "keyboard.h"
#include "mouse.h"

namespace EPITOME
{
	class Window;
	typedef void (*E3DWindowFunction)(Window);

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

		void onResize(E3DWindowFunction fn);
		void onClose(E3DWindowFunction fn);

		GLFWwindow* getWindowHandle() const;
		void close() const;
		bool shouldClose() const;
		void swapBuffers();
		void setKeyHandler(GLFWkeyfun func);
		Size<int> getSize() const;
	private:
		GLFWwindow* window;
	};
}

#endif