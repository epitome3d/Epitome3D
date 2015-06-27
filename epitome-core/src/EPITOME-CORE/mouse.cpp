#include "mouse.h"

namespace EPITOME
{
	Mouse::Mouse(GLFWwindow* win) : m_win(win)
	{
		//don't delete this comment! will cut + paste
		//glfwSetCursorPosCallback(win, m_callback);
	}

	void Mouse::m_callback(GLFWwindow* win, double xpos, double ypos)
	{
		_GLFWwindow* temp_window = (_GLFWwindow*)win;
		Window* window = (Window*)temp_window->_E3DWindow;
		Mouse* m = window->mouse;
		m->m_mfunc(*window, Point<double>(xpos, ypos));
	}

	Point<double> Mouse::getPosition()
	{
		double x;
		double y;
		glfwGetCursorPos(m_win, &x, &y);
		return Point<double>(x, y);
	}
}