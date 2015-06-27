#include "mouse.h"

namespace EPITOME
{
	Mouse::Mouse(GLFWwindow* win) : m_mousePos(0, 0), m_win(win)
	{
		glfwSetCursorPosCallback(win, m_callback);
	}

	void Mouse::m_callback(GLFWwindow* win, double xpos, double ypos)
	{
		_GLFWwindow* temp_window = (_GLFWwindow*)win;
		Window* window = (Window*)temp_window->_E3DWindow;
		Mouse* m = window->mouse;
		m->m_mfunc(*window, Point<double>(xpos, ypos));
	}

	Point<double> Mouse::getCursorPos()
	{
		double x;
		double y;
		glfwGetCursorPos(m_win, &x, &y);
		return Point<double>(x, y);
	}
}