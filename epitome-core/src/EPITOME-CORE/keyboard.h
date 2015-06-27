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

	typedef void(*E3DKeyFunction)(Window&, Keys, KeyState);

	struct E3DKeyFunctionState
	{
		E3DKeyFunction fn;
		short states;
		GLFWwindow* window;

		E3DKeyFunctionState()
		{
			this->fn = NULL;
			this->states = 0;
			this->window = NULL;
		}
		E3DKeyFunctionState(E3DKeyFunction fn, short states, GLFWwindow* window)
		{
			this->fn = fn;
			this->states = states;
			this->window = window;
		}
	};

	class Keyboard : public Initializable, public Updateable
	{
	public:
		static void Initialize();

		static void Update();

		//Add a window to the key manager
		static void AddWindow(Window* window);

		//Remove a window from the key manager
		static void RemoveWindow(Window* window);

		//Get the state of a key pressed
		static KeyState getState(Window* window, Keys key);

		//Test if a key was just pressed
		static bool isKeyPressed(Window* window, Keys key);

		//Test if a key is pressed
		static bool isKeyDown(Window* window, Keys key);

		//Test if a key was just released
		static bool isKeyReleased(Window* window, Keys key);

		//Calls a function when a key is pressed
		static void onKeyPressed(Window* window, Keys key, E3DKeyFunction fn);

		//Calls a function when a key is released
		static void onKeyReleased(Window* window, Keys key, E3DKeyFunction fn);

		//Clears a function from all keys
		//TODO removeKeyFunction()
		//TODO removeAllKeyFunctions()

		//TODO Get the character equivalent of a key - possible? useful?
		//static char getChar(Window window, Keys key);

	private:
		//interal key function
		static void GLFWKeyFunction(GLFWwindow*, int, int, int, int);

		static void _registerFunction(Window* window, Keys key, E3DKeyFunction fn, KeyState state);

		static KeyState _key_states[KEYS_COUNT];
		static short _key_lookup[KEYS_LOOKUP_LAST];

		static vector<short> _key_eventqueue;
	};
}