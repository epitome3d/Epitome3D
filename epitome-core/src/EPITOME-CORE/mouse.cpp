#include "mouse.h"

namespace EPITOME
{
	Point<double> Mouse::m_mouseLoc = Point<double>(0.0, 0.0);
	std::vector<Window*> Mouse::m_winVec = std::vector<Window*>();

	void Mouse::AddWindow(Window* w)
	{
		glfwSetCursorPosCallback(w->getWindowHandle(), m_callback);
		//TODO m_winVec currently serves no purpose.  Are we planning to un-globalize?
		m_winVec.push_back(w);
	}

	void Mouse::RemoveWindow(Window* w)
	{
		/* Makes use of the erase-remove idiom to remove w from the vector. */
		m_winVec.erase(std::remove(m_winVec.begin(), m_winVec.end(), w), m_winVec.end());
	}

	Point<double> Mouse::getMousePosition()
	{
		return m_mouseLoc;
	}

	void Mouse::m_callback(GLFWwindow* window, double xpos, double ypos)
	{
		m_mouseLoc.x = xpos;
		m_mouseLoc.y = ypos;
	}
}