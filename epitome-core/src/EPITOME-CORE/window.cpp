#include "window.h"

namespace EPITOME
{
	#if OPENGL
	Window::Window(int width, int height, char* title)
	{
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
			Error::Error(E3D_FAIL_INIT_GLFW, "glfwCreateWindow() failed", EP_FATAL);

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

	GLFWwindow* Window::get_window_handle() const
	{
		return window;
	}

	bool Window::should_close() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::swap_buffers()
	{
		glfwSwapBuffers(window);
	}

	void Window::set_key_handler(GLFWkeyfun func) {
		glfwSetKeyCallback(window, func);
	}

	size<int> Window::get_size() const {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		return size<int>(width, height);
	}
	#endif
}