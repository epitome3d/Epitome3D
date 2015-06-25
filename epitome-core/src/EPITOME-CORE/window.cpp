#include "window.h"

namespace EPITOME
{
	#if OPENGL
	Window* WINDOW_ACTIVE = nullptr;
	GLFWwindow* GLFW_WINDOW_ACTIVE = nullptr;
	
	WINDOW_MAP_TYPE::size_type WINDOW_MAP_DEFAULT_SIZE = 5;
	//This is not a function, visual studio is an idiot
	WINDOW_MAP_TYPE WINDOW_MAP(WINDOW_MAP_DEFAULT_SIZE, GLFW_WINDOW_TO_SIZE_T, GLFW_WINDOW_EQUALS);

	std::size_t GLFW_WINDOW_TO_SIZE_T(GLFWwindow* win)
	{
		return (std::size_t)win;
	}

	bool GLFW_WINDOW_EQUALS(GLFWwindow* one, GLFWwindow* two)
	{
		return one == two;
	}

	Window::Window(int width, int height, char* title)
	{
		//Set this instance as the owner of this window
		reference_num = 1;

		//create the window
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
			Error::Error(E3D_FAIL_CORE_INIT, "glfwCreateWindow() failed", EP_FATAL);

		//bind with keyboard and mouse
		Keyboard::AddWindow(this);
		Mouse::AddWindow(this);

		//add to map of windows and make active window
		WINDOW_MAP[window] = this;
		WINDOW_ACTIVE = this;
		GLFW_WINDOW_ACTIVE = window;

		//set focus callback
		glfwSetWindowFocusCallback(window, E3D_WindowFocusCallback);

		//TODO multithreading for multiple windows
		glfwMakeContextCurrent(window);
	}

	Window::Window(const Window& win)
	{
		reference_num = win.reference_num + 1;
		window = win.getWindowHandle();
		m_title = win.m_title;
	}

	Window::Window(Window&& win)
	{
		WINDOW_MAP[window] = this;
		reference_num = win.reference_num;
		win.reference_num = 100; //dummy large value
		window = win.window;
		m_title = win.m_title;
		win.window = NULL;
		win.m_title = NULL;
	}

	Window::~Window()
	{
		//Pointer is valid and this is the original refrence to window
		if (window && reference_num == 1)
		{
			WINDOW_MAP.erase(window);
			glfwDestroyWindow(window);
			Keyboard::RemoveWindow(this);
			Mouse::RemoveWindow(this);
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

	void Window::onResize(E3DWindowResizeFunction fn)
	{
		m_resizeFunction = fn;
		glfwSetWindowSizeCallback(window, E3D_WindowResizeCallback);
	}

	bool Window::isSizeChanged() const
	{
		return m_isResized;
	}

	void swap(Window & first, Window & second)
	{
		std::swap(first.window, second.window);
	}

	bool GLFW_WINDOW_PTR_EQUAL_TO(GLFWwindow * one, GLFWwindow * two)
	{
		return one == two;
	}

	std::size_t GLFW_WINDOW_PTR_TO_SIZE_T(GLFWwindow* win)
	{
		return (std::size_t)win;
	}

	void Window::onChangeFocus(E3DWindowFunction fn)
	{

	}

	GLFWwindow* Window::getWindowHandle() const
	{
		return window;
	}

	void Window::onClose(E3DWindowFunction fn)
	{
		m_closeFunction = fn;
		glfwSetWindowCloseCallback(window, E3D_WindowCloseCallback);
	}

	bool Window::isClosing() const
	{
		return (glfwWindowShouldClose(window) != 0);
	}

	void Window::close() const
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	bool Window::isFullscreen() const
	{
		return false;
	}

	void Window::setFullscreen(bool fullscreen)
	{
	}

	char * Window::getTitle() const
	{
		return m_title;
	}

	void Window::setTitle(char * title)
	{
		m_title = title;
		glfwSetWindowTitle(window, title);
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

	void E3D_WindowFocusCallback(GLFWwindow* window, int focus)
	{
		if (focus == GL_TRUE)
		{
			GLFW_WINDOW_ACTIVE = window;
			WINDOW_ACTIVE = WINDOW_MAP[window];
		}
	}

	//TODO: Find some way to remove code duplication w/o
	//function call overhead or macros. Perhaps template
	//wizardry could achieve this?
	void E3D_WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* win;
		if (window == GLFW_WINDOW_ACTIVE)
		{
			win = WINDOW_ACTIVE;
		}
		else
		{
			win = WINDOW_MAP[window];
		}
		win->m_resizeFunction(*win, Size<int>(width, height));
	}

	void E3D_WindowCloseCallback(GLFWwindow* window)
	{
		Window* win;
		if (window == GLFW_WINDOW_ACTIVE)
		{
			win = WINDOW_ACTIVE;
		}
		else
		{
			win = WINDOW_MAP[window];
		}
		win->m_closeFunction(*win);
	}
	#endif
}