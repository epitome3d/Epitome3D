#pragma once

#include "utils.h"
#include "window.h"
#include "keys.h"
#include <GLFW/glfw3.h>

namespace EPITOME
{
	//static void(*_E3D_keyCallbackFn)(GLFWwindow*, int, int, int, int);

	class Window; //forward declaration of Window to solve circular reference issues

	typedef void(*E3DKeyFunction0)();
	typedef void(*E3DKeyFunction1)(Keys);
	typedef void(*E3DKeyFunction2)(Keys, KeyState);
	typedef void(*E3DKeyFunction3)(Keys, KeyState, Window);

	class Keyboard
	{
	public:
		//Add a window to the key manager
		static void AddWindow(Window* window);

		//Get the state of a key pressed on a particular window
		static KeyState getState(Window window, Keys key);
		//Test if a key is pressed
		static bool isPressed(Window window, Keys key);

		//Get the character equivalent of a key
		//Includes modifiers
		static char getChar(Window window, Keys key);
		
		//Calls a function when a key is pressed
		template<typename T>
		static bool onPressed(Window window, Keys key, T fn);
	private:
		//interal key function
		static void GLFWKeyFunction(GLFWwindow*, int, int, int, int);

		//list of keys and functions
	};
	template <typename T>
	inline bool Keyboard::onPressed(Window window, Keys key, T fn)
	{
		static_assert(std::is_void<()>::value || std::is_void<(Window, Keys)>::value, "onPressed: function T must be an E3DKeyFunction");
		
	}
}