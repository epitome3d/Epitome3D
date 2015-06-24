#pragma once

#include <algorithm>
#include <vector>

#include "window.h"
#include "utils.h"

namespace EPITOME
{
	/* Forward declaration to prevent circular references */
	class Window;

	//TODO is using the static keyword OK here?
	static class Mouse : public Initializable
	{
	public:
		//TODO should this be Mouse() instead?
		static void Initialize();

		static void AddWindow(Window* w);

		static void RemoveWindow(Window* w);

		//TODO I'm worried this might mess up when using multiple monitors and multiple windows
		//TODO Make this function NOT global, but with a Window parameter?
		static Point<double> getMousePosition();
	private:
		//TODO specify by Window's address?
		//vector<Window*> and vector<Point<double>>
		static Point<double> m_mouseLoc;
		static std::vector<Window*> m_winVec;
		static void m_callback(GLFWwindow* window, double xpos, double ypos);
	};
}