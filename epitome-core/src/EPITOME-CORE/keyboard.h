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

	/********************************************
	 *      LARGE BANNER NOTE TO ARTHUR         *
	 ********************************************
	 I removed a lot of the Window classes from
	 the functions, because you weren't storing
	 a keyboard class per window, or storing the
	 windows in a vector or anything, and unless
	 I were to change the API, I'm not sure how
	 you'd get that done. Additionally, for the
	 GLFWKeyFunction below to determine which
	 Window the key was pressed on, we'd need some
	 GLFWwindow -> Window system that we don't have
	 right now, and I'd rather not do a vector
	 loop on every key press. Last, I combined
	 the onPressed and onReleased functions, so
	 that this way the user can be notified when
	 any key event occurs, and having another
	 vector for key functions seemed a little
	 wasteful. I think the user can figure out the
	 KeyState on their own.
	 
	 I know it would be ideal to have a Window
	 tracking system, but I thought it might be
	 best to leave the API in this state until
	 we could come up with an improved design.
	 
	 Also it seems that the GLFWKeyFun contains
	 much more info than the E3D version (e.g.
	 scancode, modifier keys) and I wanted to
	 dicuss potentially adding them to our key
	 fun. I haven't done it yet because I thought
	 you may have had a reason for the omission.

	 Thoughts?
	 */
	typedef void(*E3DKeyFunction)(Keys, KeyState);

	class Keyboard : public Initializable
	{
	public:
		//TODO Set up the internal vectors here
		static void Initialize();

		//Add a window to the key manager
		static void AddWindow(Window* window);

		//Remove a window from the key manager
		static void RemoveWindow(Window* window);

		//Get the state of a key pressed
		static KeyState getState(Keys key);

		//Test if a key is pressed
		static bool isPressed(Keys key);

		//Calls a function when something happens to a key
		static void onKeyEvent(Keys key, E3DKeyFunction fn);

		//Clears a function from all keys
		//TODO removeKeyFunction()
		//TODO removeAllKeyFunctions()

		//TODO Get the character equivalent of a key - possible? useful?
		//static char getChar(Window window, Keys key);

	private:
		//interal key function
		static void GLFWKeyFunction(GLFWwindow*, int, int, int, int);

		static vector<KeyState> _key_states;
		static vector<E3DKeyFunction> _key_function;

		static vector<short> _key_lookup_GLFW;
	};
}