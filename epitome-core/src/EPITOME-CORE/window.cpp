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

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	GLFWwindow* Window::get_window_handle() const
	{
		return window;
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