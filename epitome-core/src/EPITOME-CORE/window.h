#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3internal.h>

#include "error.h"
#include "utils.h"
#include "memory.h"
#include "keyboard.h"
#include "mouse.h"
#include "display.h"

namespace EPITOME
{
	//Forward declaration of classes so that the below can access it
	class Window;
	struct Display;
	struct VideoMode;

	//Define types of functions used as callbacks
	typedef std::function<void(Window&)> E3DWindowFunction;
	typedef std::function<void(Window&, Size<int>)> E3DWindowResizeFunction;

	//Callback used for focus that modifies the map and active variables below
	void E3D_WindowFocusCallback(GLFWwindow* window, int focus);
	void E3D_WindowResizeCallback(GLFWwindow* window, int width, int height);
	void E3D_WindowCloseCallback(GLFWwindow* window);

	//Holds pointer to active window and active GLFW window
	extern GLFWwindow* GLFW_WINDOW_ACTIVE;
	extern Window* WINDOW_ACTIVE;

	enum WindowMode
	{
		E3D_WINDOW_MODE_WINDOWED,
		E3D_WINDOW_MODE_FULLSCREEN,
		E3D_WINDOW_MODE_BORDERLESS,
		E3D_WINDOW_MODE_NOTCREATED
	};

	#define E3D_MACRO_WINDOW_REQUIRE_INIT if (this->mode == E3D_WINDOW_MODE_NOTCREATED) { Error(E3D_COMPONENT_NOT_INITIALIZED, "Must create the window before running this method.  Run setMode*() to create the window."); }

	class Window : public Disposable
	{
	public:
		//Constructors, destructors, and the like
		Window(int width, int height, const char* title, WindowMode mode = WindowMode::E3D_WINDOW_MODE_WINDOWED);
		Window(const Window&);
		Window(Window&&);
		inline ~Window() { dispose(); }

		inline static Window* getActiveWindow()
		{
			return WINDOW_ACTIVE;
		}

		//Copy-and-swap idiom
		Window& operator=(Window other);
		friend void swap(Window& first, Window& second);

		void dispose();
		void render();

		//begin drawing on this window - sets this window as current
		void beginDraw();

		bool isActive();

		void onResize(E3DWindowResizeFunction fn);
		bool isSizeChanged() const;
		//Get the size of the framebuffer, in pixels
		Size<int> getBufferSize();
		//Get the size of the window, in screen coordinates
		Size<int> getWindowSize();
		//Set the size of the window, in screen coordinates
		//In fullscreen, this changes the size of the framebuffer
		void setWindowSize(int width, int height);

		Point<int> getPosition() const;
		void setPosition(int x, int y);
		void onPositionChange();
		bool isPositionChanged();

		void onClose(E3DWindowFunction fn);
		bool isClosing() const;
		void close() const;
		void cancelClose() const;

		void hide();
		void show();
		bool isVisible();

		inline WindowMode getMode() { return mode; }
		void setModeFullscreen(Display display);
		void setModeFullscreen(Display display, VideoMode mode);
		void setModeWindowed();
		void setModeBorderless();
		Display getDisplay();

		char* getTitle() const;
		void setTitle(char* title);

		//TODO decrease the number of methods here?
		bool isMinimized() const;
		void minimize();
		void restore();
		void onMinimize(E3DWindowFunction fn);
		bool isMinimizing() const;
		void onRestore(E3DWindowFunction fn);
		bool isRestoring() const;

		friend class Keyboard;
		Keyboard* keyboard;

		friend class Mouse;
		Mouse* mouse;

		void onChangeFocus(E3DWindowFunction fn);
		//TODO void focus() - GLFW doesn't do that yet, so we should add it back to GLFW
		
		//TODO there are probably more at http://www.glfw.org/docs/latest/window.html

		GLFWwindow* getHandle() const;

		//TODO delete this method?  Replace with an instance of Keyboard?
		void setKeyHandler(GLFWkeyfun func);

		E3DWindowResizeFunction m_resizeFunction;
		E3DWindowFunction m_closeFunction;

		static Window* _getWindow(GLFWwindow*);
	private:
		WindowMode mode;
		unsigned int reference_num;
		GLFWwindow* window;
		bool m_isResized;
		char* m_title; //required b/c can't get title through GLFW
		int width, height;
		
		Display* m_display;

		void _swapBuffers();
		void _createGLFWWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	};
}