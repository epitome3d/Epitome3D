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

	/*class Mouse
	{
	public:

		static void AddWindow(Window* w);

		static void RemoveWindow(Window* w);

		static Point<double> getMousePosition(Window* w);

	private:
		static Point<double> _mouseLoc;
		static void _callback(GLFWwindow* window, double xpos, double ypos);
	};*/

	class Mouse
	{
	public:
		Mouse(GLFWwindow* win);
		//~Mouse();
		//void setCallback(E3D_MouseFunction mfunc);

		Point<double> m_mousePos;
		friend class Window;

	private:
		static void m_callback(GLFWwindow* window, double xpos, double ypos);
		GLFWwindow* m_win;
		E3D_MouseFunction m_mfunc;
	};
}