#ifndef EPITOME_GL_WINDOW
#define EPITOME_GL_WINDOW

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "error.h"
#include "utils.h"
#include "memory.h"
#include "keyboard.h"
#include "mouse.h"

namespace EPITOME
{
	class Window;
	typedef void (*E3DWindowFunction)(Window&);
	typedef void(*E3DWindowResizeFunction)(Window&, Size<int>);
	typedef std::unordered_map<GLFWwindow*, Window*, std::function<std::size_t(GLFWwindow*)>, std::function<bool(GLFWwindow*, GLFWwindow*)>> WINDOW_MAP_TYPE;

	std::size_t GLFW_WINDOW_TO_SIZE_T(GLFWwindow* win);
	bool GLFW_WINDOW_EQUALS(GLFWwindow* one, GLFWwindow* two);
	void E3D_WindowFocusCallback(GLFWwindow* window, int focus);

	class Window : public Disposable, public Updateable
	{
	public:
		Window(int width, int height, char* title);
		Window(const Window&);
		Window(Window&&);
		~Window();

		Window& operator=(Window other);
		friend void swap(Window& first, Window& second);

		inline void Dispose() { this->~Window(); }
		void Update();

		void onResize(E3DWindowFunction fn);
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

		//TODO change to E3DFocusFunction
		void onChangeFocus(E3DWindowFunction fn);
		
		//TODO there are probably more at http://www.glfw.org/docs/latest/window.html

		GLFWwindow* getWindowHandle() const;
		
		//TODO rename to something prettier
		void swapBuffers();
		//TODO delete this method?  Replace with an instance of Keyboard?
		void setKeyHandler(GLFWkeyfun func);
	private:
		unsigned int reference_num;
		GLFWwindow* window;
		bool m_isResized;
		char* m_title; //required b/c can't get title through GLFW
	};
}

#endif