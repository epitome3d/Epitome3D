#include "mouse.h"

namespace EPITOME
{
	Point<double> Mouse::_mouseLoc = Point<double>(0.0, 0.0);

	void Mouse::AddWindow(Window* w)
	{
		glfwSetCursorPosCallback(w->getWindowHandle(), _callback);
	}

	void Mouse::RemoveWindow(Window* w)
	{
		/* Makes use of the erase-remove idiom to remove w from the vector. */
		//m_winVec.erase(std::remove(m_winVec.begin(), m_winVec.end(), w), m_winVec.end());
	}

	Point<double> Mouse::getMousePosition()
	{
		return _mouseLoc;
	}

	void Mouse::_callback(GLFWwindow* window, double xpos, double ypos)
	{
		_mouseLoc.x = xpos;
		_mouseLoc.y = ypos;
	}
}