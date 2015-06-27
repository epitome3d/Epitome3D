#include "mouse.h"

namespace EPITOME
{
	Point<double> Mouse::m_mouseLoc = Point<double>(0.0, 0.0);

	void Mouse::AddWindow(Window* w)
	{
		glfwSetCursorPosCallback(w->getWindowHandle(), m_callback);
		//TODO m_winVec currently serves no purpose.  Are we planning to un-globalize?
	}

	void Mouse::RemoveWindow(Window* w)
	{
		
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