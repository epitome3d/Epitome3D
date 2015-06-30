#include "window.h"

namespace EPITOME
{
	#if OPENGL
	//Defining active window variables
	Window* WINDOW_ACTIVE = nullptr;
	GLFWwindow* GLFW_WINDOW_ACTIVE = nullptr;

	Window::Window(int width, int height, const char* title)
	{
		//Set this instance as the owner of this window
		reference_num = 1;

		//create the window
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
			Error(E3D_FAIL_CORE_INIT, "glfwCreateWindow() failed", EP_FATAL);

		//set a reference pointer back to this window
		((_GLFWwindow*)window)->_E3DWindow = this;

		//bind with keyboard and mouse
		keyboard = new Keyboard(this);
		mouse = new Mouse(window);

		//make active window
		WINDOW_ACTIVE = this;
		GLFW_WINDOW_ACTIVE = window;

		//set focus callback
		glfwSetWindowFocusCallback(window, E3D_WindowFocusCallback);

		//TODO multithreading for multiple windows
		//beginDraw();
	}

	//Copy constructor
	//Currently has few, if any, acceptable uses
	//Soon to be deprecated
	Window::Window(const Window& win)
	{
		reference_num = win.reference_num + 1;
		window = win.getHandle();
		m_title = win.m_title;
	}

	//Move constructor
	//Extracts life force of another window
	//and puts it into this one.
	Window::Window(Window&& win)
	{
		reference_num = win.reference_num;
		win.reference_num = 100; //dummy large value
		window = win.window;
		m_title = win.m_title;
		win.window = NULL;
		win.m_title = NULL;
	}

	//The window is about to die
	Window::~Window()
	{
		//Pointer is valid and this is the original refrence to window
		if (window && reference_num == 1)
		{
			glfwDestroyWindow(window);
			delete keyboard;
			delete mouse;
		}
	}

	Window* Window::getWindow(GLFWwindow* window)
	{
		return ((Window*)((_GLFWwindow*)window)->_E3DWindow);
	}

	Window& Window::operator=(Window other)
	{
		swap(*this, other);

		return *this;
	}

	void Window::render()
	{
		_swapBuffers();
	}

	void Window::beginDraw()
	{
		glfwMakeContextCurrent(window);
	}

	bool Window::isActive()
	{
		return (window == GLFW_WINDOW_ACTIVE);
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

	GLFWwindow* Window::getHandle() const
	{
		return window;
	}

	void Window::onClose(E3DWindowFunction fn)
	{
		//TODO should we have a central way of storing and deinstancing callbacks?
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

	void Window::cancelClose() const
	{
		glfwSetWindowShouldClose(window, GL_FALSE);
	}

	void Window::hide()
	{
		glfwHideWindow(window);
	}

	void Window::show()
	{
		glfwShowWindow(window);
	}

	bool Window::isVisible()
	{
		return glfwGetWindowAttrib(window, GLFW_VISIBLE) != 0;
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
	
	void Window::_swapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void Window::setKeyHandler(GLFWkeyfun func) {
		glfwSetKeyCallback(window, func);
	}

	Size<int> Window::getBufferSize() const {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		return Size<int>(width, height);
	}

	Size<int> Window::getWindowSize() const {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		return Size<int>(width, height);
	}

	void Window::setWindowSize(int width, int height)
	{
		glfwSetWindowSize(window, width, height);
	}

	Point<int> Window::getPosition() const
	{
		int x, y;
		glfwGetWindowPos(window, &x, &y);
		return Point<int>(x, y);
	}

	void Window::setPosition(int x, int y)
	{
		glfwSetWindowPos(window, x, y);
	}

	void E3D_WindowFocusCallback(GLFWwindow* window, int focus)
	{
		if (focus == GL_TRUE)
		{
			GLFW_WINDOW_ACTIVE = window;
			WINDOW_ACTIVE = Window::getWindow(window);
		}
	}

	//TODO: Find some way to remove code duplication w/o function call overhead or macros. Perhaps template wizardry could achieve this?
	void E3D_WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* win = Window::getWindow(window);
		win->m_resizeFunction(*win, Size<int>(width, height));
	}

	void E3D_WindowCloseCallback(GLFWwindow* window)
	{
		Window* win = Window::getWindow(window);
		win->m_closeFunction(*win);
	}
	#endif
}