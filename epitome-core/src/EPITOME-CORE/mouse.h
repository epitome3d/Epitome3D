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

		static Point<double> getMousePosition(Window* w);

	private:
		static Point<double> _mouseLoc;
		static void _callback(GLFWwindow* window, double xpos, double ypos);
	};
}