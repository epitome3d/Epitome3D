#pragma once

#include <algorithm>
#include <vector>

#include "window.h"

namespace EPITOME
{
	/* Forward declaration to prevent circular references */
	class Window;

	namespace Mouse
	{
		void AddWindow(Window* w);

		void RemoveWindow(Window* w);

		Point<double> getMousePosition();

		/* 
		 * These are never to be used, only accessed through whatever get methods may exist.
		 * A better method for encapsulation should be discussed, however I am reluctant to
		 * make Mouse a class, because it should only ever need to be initialized once, if
		 * the one mouse object model is to be used.
		 */
		static Point<double> m_mouseLoc(0, 0);
		static std::vector<Window*> m_winVec;
		static void m_callback(GLFWwindow* window, double xpos, double ypos);
	}
}