#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"
#include "window.h"
#include <vector>
using namespace std;

namespace EPITOME
{
	//TODO how should we handle classes that are unique features of GLFW?  (ex. gamma ramp and monitors)

	struct GammaRamp
	{
		unsigned short* red;
		unsigned short* green;
		unsigned short* blue;
		unsigned int size;
	};

	struct VideoMode
	{

	};

	struct Display
	{
	public:
		Display();
		Display(GLFWmonitor* monitor);

		//TODO this might not make much sense as windows can move from monitor to monitor - as long as they are not fullscreen
		//TODO addWindow and removeWindow are really used to set the window that will be fullscreen
		//void addWindow(Window* window);
		//void removeWindow(Window* window);

		//Gets the name of the display
		const char* getName();
		//Gets the position of the display relative to the origin, in pixels
		Point<int> getPosition();
		//Gets the physical size of the display, in millimeters
		Size<int> getPhysicalSize();

	private:
		GLFWmonitor* monitor;
		//vector<Window*> windows;

		#ifndef OPENGL
		char* name;
		Point<int> position;
		Size<int> size;
		#endif
		GammaRamp gamma;
	};

	class Displays
	{
		static Display getPrimary();
		static Display* getAllDisplays(int& count);

	private:
		static Display getDisplay(GLFWmonitor* monitor);
	};
}