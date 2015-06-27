#include "mouse.h"

namespace EPITOME
{
	/*Point<double> Mouse::_mouseLoc = Point<double>(0.0, 0.0);
	static const Point<double> _emptyLoc(0, 0);

	void Mouse::AddWindow(Window* w)
	{
		glfwSetCursorPosCallback(w->getWindowHandle(), _callback);
	}

	void Mouse::RemoveWindow(Window* w)
	{
		/* Makes use of the erase-remove idiom to remove w from the vector. * /
		//m_winVec.erase(std::remove(m_winVec.begin(), m_winVec.end(), w), m_winVec.end());
	}

	Point<double> Mouse::getMousePosition(Window* win)
	{
		if (win == WINDOW_ACTIVE)
		{
			return _mouseLoc;
		}
		else
		{
			return _emptyLoc;
		}
	}

	void Mouse::_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (window != GLFW_WINDOW_ACTIVE)
			return;
		_mouseLoc.x = xpos;
		_mouseLoc.y = ypos;
	}*/

	Mouse::Mouse(Window* win) : m_mousePos(0, 0), m_win(win), m_glfw_win(win->getWindowHandle()) {}

	void Mouse::m_callback(GLFWwindow* win, double xpos, double ypos)
	{
		if (win == GLFW_WINDOW_ACTIVE)
		{

		}
	}
}