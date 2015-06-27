#include "keyboard.h"

namespace EPITOME
{
	vector<short> Keyboard::_key_eventqueue = vector<short>();
	KeyState Keyboard::_key_states[KEYS_COUNT] = { };
	E3DKeyFunctionState Keyboard::_key_function[KEYS_COUNT];
	short Keyboard::_key_lookup[KEYS_LOOKUP_LAST] = { };

	void Keyboard::Initialize()
	{
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

		//send key to upstream function, if set AND if the current state matches the function states
		E3DKeyFunction fn = _key_function[loc].fn;
		if (fn != NULL && window == GLFW_WINDOW_ACTIVE && window == _key_function[loc].window)
		{
			if ((_key_function[loc].states & _key_states[loc]) > 0)
				fn(*WINDOW_ACTIVE, (EPITOME::Keys)loc, _key_states[loc]);
		}
	}

	KeyState Keyboard::getState(Window* window, Keys key)
	{
		return (window->isActive()) ? _key_states[key] : KeyState::KEYS_NOTPRESSED;
	}

	bool Keyboard::isKeyPressed(Window* window, Keys key)
	{
		KeyState state = getState(window, key);
		return (state == KeyState::KEYS_PRESSED);
	}
	bool Keyboard::isKeyDown(Window* window, Keys key)
	{
		KeyState state = getState(window, key);
		return (state == KeyState::KEYS_PRESSED || state == KeyState::KEYS_HELD);
	}

	bool Keyboard::isKeyReleased(Window* window, Keys key)
	{
		KeyState state = getState(window, key);
		return (state == KeyState::KEYS_RELEASED);
	}

	void Keyboard::onKeyPressed(Window* window, Keys key, E3DKeyFunction fn)
	{
		_registerFunction(window, key, fn, KeyState::KEYS_PRESSED);
	}

	void Keyboard::onKeyReleased(Window* window, Keys key, E3DKeyFunction fn)
	{
		_registerFunction(window, key, fn, KeyState::KEYS_RELEASED);
	}

	//TODO problems with multiple windows
	void Keyboard::_registerFunction(Window* window, Keys key, E3DKeyFunction fn, KeyState state)
	{
		_key_function[key] = E3DKeyFunctionState(fn, _key_function[key].states | state, window->getWindowHandle());
	}
}