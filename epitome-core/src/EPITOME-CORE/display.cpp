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

	VideoMode Display::getBestVideoMode()
	{
		int count;
		const GLFWvidmode* modes = glfwGetVideoModes(monitor, &count);

		int maxWidth = 0;
		int maxHeight = 0;
		int maxLoc = 0;
		for (int i = 0; i < count; i++)
		{
			if (modes[i].width > maxWidth)
				maxWidth = modes[i].width; maxLoc = i;
			if (modes[i].height > maxHeight)
				maxHeight = modes[i].height; maxLoc = i;
		}

		GLFWvidmode best = modes[maxLoc];
		return VideoMode(best);
	}

	Display Displays::getPrimary()
	{
		return Display(glfwGetPrimaryMonitor());
	}

	Display* Displays::getAllDisplays(int& count)
	{
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		//allocate the array
		
		Display* displays = new Display[count];

		//copy the arrays
		for (int i = 0; i < count; i++)
			displays[i] = monitors[i];

		return displays;
		//TODO we MUST delete this array!!!  MEMORY LEAK ALERT
	}

	VideoMode::VideoMode()
	{
		_setVideoMode(1, 1, 1, 3);
	}

	void VideoMode::_setVideoMode(unsigned int width, unsigned int height, unsigned int refreshRate, unsigned int bitsPerPixel)
	{
		if (height == 0 || width == 0 || refreshRate == 0 || bitsPerPixel == 0 || bitsPerPixel % 3 != 0)
			Error(E3D_INVALID_PARAMETER, "A parameter is invalid.");

		this->width = width;
		this->height = height;
		this->refreshRate = refreshRate;
		this->bitsPerPixel = bitsPerPixel;

		unsigned int gcd = Math::gcd<unsigned int>(width, height);
		this->ratio = Size<unsigned int>((unsigned int)floor(width / gcd), (unsigned int)floor(height / gcd));
	}

	VideoMode::VideoMode(GLFWvidmode& mode)
	{
		this->mode = mode;
		_setVideoMode(mode.width, mode.height, mode.refreshRate, mode.redBits + mode.greenBits + mode.blueBits);
	}

	ColorCorrection::ColorCorrection()
	{
		//TODO not implemented
	}

	ColorCorrection::ColorCorrection(double gamma, double brightness, double contrast)
	{
		//TODO not implemented
	}

}