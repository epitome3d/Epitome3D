#include "mouse.h"

namespace EPITOME
{
	namespace Mouse
	{
		void AddWindow(Window* w)
		{
			glfwSetCursorPosCallback(w->getWindowHandle(), m_callback);
			m_winVec.push_back(w);
		}

		void RemoveWindow(Window* w)
		{
			/* Makes use of the erase-remove idiom to remove w from the vector. */
			m_winVec.erase(std::remove(m_winVec.begin(), m_winVec.end(), w), m_winVec.end());
		}

		Point<double> getMousePosition()
		{
			return m_mouseLoc;
		}

		static void m_callback(GLFWwindow* window, double xpos, double ypos)
		{
			m_mouseLoc.x = xpos;
			m_mouseLoc.y = ypos;
		}
	}
}