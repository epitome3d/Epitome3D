#include "mouse.h"

namespace EPITOME
{
	Mouse::Mouse(GLFWwindow* win) : m_mousePos(0, 0), m_win(win)
	{
		glfwSetCursorPosCallback(win, m_callback);
	}

	void Mouse::m_callback(GLFWwindow* win, double xpos, double ypos)
	{
		//call callback function here later
	}

	Point<double> Mouse::getCursorPos()
	{
		double x;
		double y;
		glfwGetCursorPos(m_win, &x, &y);
		return Point<double>(x, y);
	}
}