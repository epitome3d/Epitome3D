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

	class Keyboard
	{
	public:
		Keyboard(Window* window);
		~Keyboard();

		void Update();

		//Get the state of a key pressed
		KeyState getState(Keys key);

		//Test if a key was just pressed
		bool isKeyPressed(Keys key);

		//Test if a key is pressed
		bool isKeyDown(Keys key);

		//Test if a key was just released
		bool isKeyReleased(Keys key);

		//Calls a function when a key is pressed
		void onKeyPressed(Keys key, E3DKeyFunction fn);

		//Calls a function when a key is released
		void onKeyReleased(Keys key, E3DKeyFunction fn);

		//Clears a function from all keys
		//TODO removeKeyFunction()
		//TODO removeAllKeyFunctions()

		//TODO Get the character equivalent of a key - possible? useful?
		//static char getChar(Window window, Keys key);

	private:
		static void Initialize();

		//interal key function
		static void GLFWKeyFunction(GLFWwindow*, int, int, int, int);

		void _registerFunction(Keys key, E3DKeyFunction fn, KeyState state);

		static bool _isInitialized;
		static KeyState _key_states[KEYS_COUNT];
		static short _key_lookup[KEYS_LOOKUP_LAST];

		Window* _window;
		E3DKeyFunctionState _key_function[KEYS_COUNT];
		vector<short> _key_eventqueue;
	};
}