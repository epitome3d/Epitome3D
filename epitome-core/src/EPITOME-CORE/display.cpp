#include "display.h"

namespace EPITOME
{
	Display::Display()
	{
		this->monitor = nullptr;
	}
	Display::Display(GLFWmonitor* monitor)
	{
		this->monitor = monitor;
	}

	const char* Display::getName()
	{
		return glfwGetMonitorName(monitor);
	}

	Point<int> Display::getPosition()
	{
		int x, y;
		glfwGetMonitorPos(monitor, &x, &y);
		return Point<int>(x, y);
	}

	Size<int> Display::getPhysicalSize()
	{
		int w, h;
		glfwGetMonitorPhysicalSize(monitor, &w, &h);
		return Size<int>(w, h);
	}

	Display Displays::getPrimary()
	{
		return getDisplay(glfwGetPrimaryMonitor());
	}

	Display* Displays::getAllDisplays(int& count)
	{
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		//allocate the array
		Display* displays = new Display[count];
		return displays;
		//TODO we MUST delete this array!!!  MEMORY LEAK ALERT
	}

	Display Displays::getDisplay(GLFWmonitor* monitor)
	{
		return Display(monitor);
	}
}