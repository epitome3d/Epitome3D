#pragma once

#include <algorithm>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3internal.h>

#include "window.h"
#include "utils.h"

namespace EPITOME
{
	/* Forward declaration to prevent circular references */
	class Window;

	typedef std::function<bool(Window&, Point<double>)> E3D_MouseFunction;
	class Mouse
	{
	public:
		Mouse(GLFWwindow* win);
		void onMove(E3D_MouseFunction mfunc);
		void unsetMove();
		Point<double> getPosition();
		friend class Window;

	private:
		static void m_callback(GLFWwindow* window, double xpos, double ypos);
		GLFWwindow* m_win;
		E3D_MouseFunction m_mfunc;
	};
}