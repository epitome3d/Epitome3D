#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"
#include "window.h"
#include "mathbasic.h"
#include <vector>
using namespace std;

namespace EPITOME
{
	//TODO how should we handle classes that are unique features of GLFW?  (ex. gamma ramp and monitors)

	struct ColorCorrection
	{
	public:
		ColorCorrection();
		ColorCorrection(double gamma, double brightness, double contrast);

		inline double getGamma() { return gamma; }
		inline double getBrightness() { return brightness; }
		inline double getContrast() { return contrast; }

		inline unsigned short* getRedRamp(int& size) { size = this->size; return red; }
		inline unsigned short* getGreenRamp(int& size) { size = this->size; return green; }
		inline unsigned short* getBlueRamp(int& size) { size = this->size; return blue; }
	private:
		//The gamma value of the ramp, a double greater than zero
		double gamma;
		//The brightness value of the ramp
		double brightness;
		//The contrast value of the ramp
		double contrast;
		//Array containing output red values for input red values
		unsigned short* red;
		//Array containing output green values for input green values
		unsigned short* green;
		//Array containing output blue values for blue green values
		unsigned short* blue;
		//Array containing output green values for input green values
		unsigned int size;
	};

	struct VideoMode
	{
	public:
		VideoMode();
		VideoMode(GLFWvidmode& mode);
		VideoMode(unsigned int width, unsigned int height, unsigned int refreshRate, unsigned int bitsPerPixel);

		//Gets the size of the video mode, in pixels
		inline Size<unsigned int> getSize() { return Size<unsigned int>(width, height); }
		//Gets the reduced ratio of the video mode, such as 16:9
		inline Size<unsigned int> getRatio() { return ratio; }
		//Gets the refresh rate of the video mode in Hertz (Hz)
		inline unsigned int getRefreshRate() { return refreshRate; }
		//Gets the bits per pixel value of the red, green, and blue fields
		inline unsigned int getBitsPerPixel() { return bitsPerPixel; }
	private:
		//Width in pixels
		unsigned int width;
		//Height in pixels
		unsigned int height;
		//Ratio of the width and height in pixels
		Size<unsigned int> ratio;
		//Refresh rate of the monitor in Hertz (Hz)
		unsigned int refreshRate;
		//Bits per pixel of the red, green, and blue fields
		unsigned int bitsPerPixel;

		void _setVideoMode(unsigned int width, unsigned int height, unsigned int refreshRate, unsigned int bitsPerPixel);
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
		//Gets all video modes
		VideoMode* getAllVideoModes(int& count);
		//Gets the best video mode
		VideoMode getBestVideoMode();

		ColorCorrection getColorCorrection();
		void setColorCorrection(ColorCorrection correction);

	private:
		GLFWmonitor* monitor;
		ColorCorrection correction;
		Window* window;

		#ifndef OPENGL
		char* name;
		Point<int> position;
		Size<int> size;
		#endif
	};

	class Displays
	{
	public:
		static Display getPrimary();
		static Display* getAllDisplays(int& count);
	};
}