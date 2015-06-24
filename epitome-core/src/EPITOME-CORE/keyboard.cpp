#include "keyboard.h"

namespace EPITOME
{
	vector<short> Keyboard::_key_eventqueue = vector<short>();
	KeyState Keyboard::_key_states[KEYS_COUNT] = { };
	E3DKeyFunctionState Keyboard::_key_function[KEYS_COUNT];
	short Keyboard::_key_lookup[KEYS_LOOKUP_LAST] = { };

	void Keyboard::Initialize()
	{
		//the below removed because unexpected keys default to UNKNOWN
		//for (size_t i = 0; i < KEYS_COUNT; i++)
		//{
		//	_key_lookup[i] = -1;
		//}
		for (short i = 0; i < KEYS_COUNT; i++)
		{
			_key_states[i] = KeyState::KEYS_NOTPRESSED;
			_key_function[i] = E3DKeyFunctionState();
			_key_lookup[KEYS_LOOKUP[i]] = i;
		}
		_key_eventqueue.clear();
	}
		
	void Keyboard::Update()
	{
		for each (short key in _key_eventqueue)
		{
			//get key state
			KeyState state = _key_states[key];

			//update key state if necessary
			if (state == KeyState::KEYS_PRESSED)
				_key_states[key] = KeyState::KEYS_HELD;
			if (state == KeyState::KEYS_RELEASED)
				_key_states[key] = KeyState::KEYS_NOTPRESSED;
	}

		//reset event queue
		_key_eventqueue.clear();
	}

	void Keyboard::AddWindow(Window* window)
	{
		GLFWkeyfun fn = glfwSetKeyCallback(window->getWindowHandle(), GLFWKeyFunction);
		if (!fn)
			Error(E3D_FAIL_CORE_INIT, "glfwSetKeyCallback() failed");
	}

	void Keyboard::RemoveWindow(Window * window)
	{
		glfwSetKeyCallback(window->getWindowHandle(), NULL);
	}

	/*
	* The GLFW key function override
	* Action can be GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT
	*/
	void Keyboard::GLFWKeyFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//get E3D key equivalent
		const short loc = _key_lookup[key];

		//set new key state
		_key_states[loc] = (action == GLFW_PRESS) ? KeyState::KEYS_PRESSED :
			(action == GLFW_RELEASE) ? KeyState::KEYS_RELEASED :
			(action == GLFW_REPEAT) ? KeyState::KEYS_PRESSED : //TODO not sure what to do for GLFW_REPEAT
			KeyState::KEYS_NOTPRESSED;  

		//add key to update queue - update next frame
		_key_eventqueue.push_back(loc);

		//send key to upstream function, if set
		E3DKeyFunction fn = _key_function[loc].fn;
		if (fn != NULL)
			fn((EPITOME::Keys)loc, _key_states[loc]);
	}

	KeyState Keyboard::getState(Keys key)
	{
		return _key_states[key];
	}

	bool Keyboard::isPressed(Keys key)
	{
		KeyState state = getState(key);
		return (state == KeyState::KEYS_PRESSED);
	}
	bool Keyboard::isPressedOrHeld(Keys key)
	{
		KeyState state = getState(key);
		return (state == KeyState::KEYS_PRESSED || state == KeyState::KEYS_HELD);
	}

	bool Keyboard::isReleased(Keys key)
	{
		KeyState state = getState(key);
		return (state == KeyState::KEYS_RELEASED);
	}

	void Keyboard::onPressed(Keys key, E3DKeyFunction fn)
	{
		_registerFunction(key, fn, KeyState::KEYS_PRESSED);
	}

	void Keyboard::onReleased(Keys key, E3DKeyFunction fn)
	{
		_registerFunction(key, fn, KeyState::KEYS_RELEASED);
	}

	void Keyboard::_registerFunction(Keys key, E3DKeyFunction fn, KeyState state)
	{
		_key_function[key] = E3DKeyFunctionState(fn, _key_function[key].states | state);
	}
}