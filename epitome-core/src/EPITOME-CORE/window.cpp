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

	Window::Window(Window&& win)
	{
		window = win.window;
		win.window = NULL;
	}

	Window::~Window()
	{
		if (window)
		{
			glfwDestroyWindow(window);
		}
	}

	Window& Window::operator=(Window other)
	{
		swap(*this, other);

		return *this;
	}

	void swap(Window & first, Window & second)
	{
		std::swap(first.window, second.window);
	}

	GLFWwindow* Window::getWindowHandle() const
	{
		return window;
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void Window::setKeyHandler(GLFWkeyfun func) {
		glfwSetKeyCallback(window, func);
	}

	Size<int> Window::getSize() const {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		return Size<int>(width, height);
	}
	#endif
}