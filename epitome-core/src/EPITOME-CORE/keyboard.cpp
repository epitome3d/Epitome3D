#include "keyboard.h"

namespace EPITOME
{
	void Keyboard::Initialize()
	{
		
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

	KeyState Keyboard::getState(Keys key)
	{
		return _key_states[key];
	}

	bool Keyboard::isPressed(Keys key)
	{
		KeyState ks = _key_states[key];
		return (ks == KEYS_PRESSED) || (ks == KEYS_HELD);
	}

	void Keyboard::onKeyEvent(Keys key, E3DKeyFunction fn)
	{
		_key_function[key] = fn;
	}

	void Keyboard::GLFWKeyFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Keys epitome_key = (Keys)_key_lookup_GLFW[key];
		E3DKeyFunction kf = _key_function[epitome_key];
		if (kf)
		{
			(epitome_key, (KeyState)action);
		}
	}
}