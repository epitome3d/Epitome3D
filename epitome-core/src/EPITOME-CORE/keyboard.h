#pragma once

#include "utils.h"
#include "window.h"
#include "keys.h"
#include <GLFW/glfw3.h>
#include <vector>
using namespace std;

namespace EPITOME
{
	//static void(*_E3D_keyCallbackFn)(GLFWwindow*, int, int, int, int);

	class Window; //forward declaration of Window to solve circular reference issues

	typedef void(*E3DKeyFunction)(Keys, KeyState, Window);

	class Keyboard : public Initializable
	{
	public:
		//TODO Set up the internal vectors here
		static void Initialize();

		//Add a window to the key manager
		static void AddWindow(Window* window);

		//Remove a window from the key manager
		static void RemoveWindow(Window* window);

		//Get the state of a key pressed on a particular window
		static KeyState getState(Window window, Keys key);

		//Test if a key is pressed
		static bool isPressed(Window window, Keys key);

		//Calls a function when a key is pressed
		static bool onPressed(Window window, Keys key, E3DKeyFunction fn);

		//Calls a function when a key is released
		static bool onReleased(Window window, Keys key, E3DKeyFunction fn);

		//Clears a function from all keys
		//TODO removeKeyFunction()
		//TODO removeAllKeyFunctions()

		//TODO Get the character equivalent of a key - possible? useful?
		//static char getChar(Window window, Keys key);

	private:
		//interal key function
		static void GLFWKeyFunction(GLFWwindow*, int, int, int, int);

		static vector<KeyState> _key_states;
		static vector<void*> _key_function;

		static vector<short> _key_lookup_GLFW;
	};
}