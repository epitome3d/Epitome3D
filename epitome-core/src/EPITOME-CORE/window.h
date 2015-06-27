#ifndef EPITOME_GL_WINDOW
#define EPITOME_GL_WINDOW

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

namespace EPITOME
{
	//Forward declaration of class so that the below can access it
	class Window;
	

	//Define types of functions used as callbacks
	typedef std::function<void(Window&)> E3DWindowFunction;
	typedef std::function<void(Window&, Size<int>)> E3DWindowResizeFunction;

	//Define class of unordered map to map windows, with custom hashing and equal functions
	typedef std::unordered_map<GLFWwindow*, Window*, std::function<std::size_t(GLFWwindow*)>, std::function<bool(GLFWwindow*, GLFWwindow*)>> WINDOW_MAP_TYPE;

	//Custom hashing and equal functions for above
	std::size_t GLFW_WINDOW_TO_SIZE_T(GLFWwindow* win);
	bool GLFW_WINDOW_EQUALS(GLFWwindow* one, GLFWwindow* two);

	//Callback used for focus that modifies the map and active variables below
	void E3D_WindowFocusCallback(GLFWwindow* window, int focus);

	//Holds pointer to active window and active GLFW window
	extern GLFWwindow* GLFW_WINDOW_ACTIVE;
	extern Window* WINDOW_ACTIVE;

	class Window : public Disposable
	{
	public:
		//Constructors, destructors, and the like
		Window(int width, int height, char* title);
		Window(const Window&);
		Window(Window&&);
		~Window();

		//Copy-and-swap idiom
		Window& operator=(Window other);
		friend void swap(Window& first, Window& second);

		inline void Dispose() { this->~Window(); }
		void Render();

		//begin drawing on this window - sets this window as current
		void beginDraw();

		bool isActive();

		void onResize(E3DWindowResizeFunction fn);
		bool isSizeChanged() const;
		Size<int> getSize() const;

		void onClose(E3DWindowFunction fn);
		bool isClosing() const;
		void close() const;

		bool isFullscreen() const;
		void setFullscreen(bool fullscreen);

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

		//TODO change to E3DFocusFunction
		void onChangeFocus(E3DWindowFunction fn);
		
		//TODO there are probably more at http://www.glfw.org/docs/latest/window.html

		GLFWwindow* getWindowHandle() const;

		//TODO delete this method?  Replace with an instance of Keyboard?
		void setKeyHandler(GLFWkeyfun func);

		friend void E3D_WindowResizeCallback(GLFWwindow* window, int width, int height);
		friend void E3D_WindowCloseCallback(GLFWwindow* window);
	private:
		unsigned int reference_num;
		GLFWwindow* window;
		bool m_isResized;
		char* m_title; //required b/c can't get title through GLFW
		E3DWindowResizeFunction m_resizeFunction;
		E3DWindowFunction m_closeFunction;
		//Do not touch - for use by mouse class only

		void _swapBuffers();
	};
}

#endif