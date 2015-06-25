#include "window.h"

namespace EPITOME
{
	#if OPENGL
	Window::Window(int width, int height, char* title)
	{
		//create the window
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
			Error::Error(E3D_FAIL_CORE_INIT, "glfwCreateWindow() failed", EP_FATAL);

		//bind with keyboard and mouse
		Keyboard::AddWindow(this);
		Mouse::AddWindow(this);

		//TODO multithreading for multiple windows
		glfwMakeContextCurrent(window);
	}

	Window::Window(const Window& win)
	{
		window = win.getWindowHandle();
	}

	Window::Window(Window&& win)
	{
		window = win.window;
		win.window = NULL;
	}

	Window::~Window()
	{
		Keyboard::RemoveWindow(this);
		Mouse::RemoveWindow(this);
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

	void Window::Update()
	{
		//TODO test if window resized here
	}

	void swap(Window & first, Window & second)
	{
		std::swap(first.window, second.window);
	}

	GLFWwindow* Window::getWindowHandle() const
	{
		return window;
	}

	bool Window::isClosing() const
	{
		return (glfwWindowShouldClose(window) != 0);
	}

	void Window::close() const
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
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
		//TODO this is the size of the buffer, in pixels!  But should we not have a getWindowSize() in screen coordinates as well?
		//TODO ex. fullscreen apps which have low pixel framebuffers but giant screens
		glfwGetFramebufferSize(window, &width, &height);

		return Size<int>(width, height);
	}
	#endif
}