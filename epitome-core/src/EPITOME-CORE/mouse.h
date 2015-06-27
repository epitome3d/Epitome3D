#pragma once

#include <algorithm>
#include <vector>

#include "window.h"
#include "utils.h"

namespace EPITOME
{
	/* Forward declaration to prevent circular references */
	class Window;

	class Mouse
	{
	public:

		static void AddWindow(Window* w);

		static void RemoveWindow(Window* w);

		static Point<double> getMousePosition();

		/* 
		 * These are never to be used, only accessed through whatever get methods may exist.
		 * A better method for encapsulation should be discussed, however I am reluctant to
		 * make Mouse a class, because it should only ever need to be initialized once, if
		 * the one mouse object model is to be used.
		 */
		static Point<double> m_mouseLoc;
		static void m_callback(GLFWwindow* window, double xpos, double ypos);
	};
}