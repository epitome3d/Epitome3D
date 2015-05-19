#include "input.h"

namespace EPITOME
{

	Input::Input()
	{
		m_directInput = 0;
		m_keyboard = 0;
		m_mouse = 0;
		m_touchdevice = false;
	}

	Input::Input(const Input& other)
	{
	}

	Input::~Input()
	{
	}

	bool Input::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, bool bindMouse)
	{
		HRESULT result;


		// Store the screen size which will be used for positioning the mouse cursor.
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		// Initialize the location of the mouse on the screen.
		m_mouseX = 0;
		m_mouseY = 0;

		// Initialize the main direct input interface.
		result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
		if(FAILED(result))
		{
			return false;
		}

		// Initialize the direct input interface for the keyboard.
		result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
		if(FAILED(result))
		{
			return false;
		}

		// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
		result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(result))
		{
			return false;
		}

		// Set the cooperative level of the keyboard to not share with other programs.
		result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if(FAILED(result))
		{
			return false;
		}

		// Now acquire the keyboard.
		result = m_keyboard->Acquire();
		if(FAILED(result))
		{
			return false;
		}

		m_touchdevice = false;

		// Initialize the direct input interface for the mouse.
		result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		if(FAILED(result))
		{
			//if fails, assume device to be a touch interface
			m_touchdevice = true;
		}

	
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		m_desktopWidth = desktop.right;
		m_desktopHeight = desktop.bottom;
		
		//get the location of the window on the screen
		m_windowX = (m_desktopWidth - screenWidth) / 2;
		m_windowY = (m_desktopHeight - screenHeight) / 2;

		if(!m_touchdevice)
		{
			// Set the data format for the mouse using the pre-defined mouse data format.
			result = m_mouse->SetDataFormat(&c_dfDIMouse);
			if(FAILED(result))
			{
				return false;
			}

			// Set the cooperative level of the mouse to share with other programs.
			if (bindMouse)
			{
				result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
			}
			else
			{
				result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			}
			if(FAILED(result))
			{
				return false;
			}

			// Acquire the mouse.
			result = m_mouse->Acquire();
			if(FAILED(result))
			{
				return false;
			}

			SetCursorPos(m_desktopWidth / 2, m_desktopHeight / 2);
			m_mouseX = m_desktopWidth / 2;
			m_mouseY = m_desktopHeight / 2;		
		}

		return true;
	}

	bool Input::Frame(bool &lost)
	{
		bool result;

		//read the current state of the keyboard
		result = ReadKeyboard(lost);
		if(!result) { return false; }

		if (!m_touchdevice)
		{
			result = ReadMouse();
			if(!result) { return false; }
		}

		//process the changes
		ProcessInput();

		return true;
	}

	void Input::Shutdown()
	{
		//release the mouse
		if(m_mouse)
		{
			m_mouse->Unacquire();
			m_mouse->Release();
			m_mouse = 0;
		}

		//release the keyboard
		if(m_keyboard)
		{
			m_keyboard->Unacquire();
			m_keyboard->Release();
			m_keyboard = 0;
		}

		//release the main interface to direct input
		if(m_directInput)
		{
			m_directInput->Release();
			m_directInput = 0;
		}

		return;
	}

	bool Input::ReadKeyboard(bool &lost)
	{
		HRESULT result;
		lost = false;

		// Read the keyboard device.
		result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
		if(FAILED(result))
		{
			// If the keyboard lost focus or was not acquired then try to get control back.
			if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				lost = true;
				m_keyboard->Acquire();
			}
			else
			{
				return false;
			}
		}
		
		return true;
	}

	bool Input::ReadMouse()
	{
		HRESULT result;

		//read the mouse device
		result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
		if (FAILED(result))
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				m_mouse->Acquire();
			}
			else
			{
				return false;
			}
		}
	
		return true;
	}

	void Input::ProcessInput()
	{	
		//update the location of the mouse cursor based on the change
		m_mouseX += m_mouseState.lX;
		m_mouseY += m_mouseState.lY;
		
		//ensure the mouse location does not exceed the screen width or height
		if(m_mouseX < 0) { m_mouseX = 0; }
		if(m_mouseY < 0) { m_mouseY = 0; }

		if(m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
		if(m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
		
		return;
	}

	bool Input::IsKeyPressed(unsigned char DIK)
	{
		// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
		if(m_keyboardState[DIK] & 0x80)
		{
			return true;
		}

		return false;
	}

	bool Input::GetMouseLocation(int& mouseX, int& mouseY)
	{
		if(!m_touchdevice)
		{
			mouseX = m_mouseX;
			mouseY = m_mouseY;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Input::SetMouseLocation(int mouseX, int mouseY)
	{
		if(!m_touchdevice)
		{
			m_mouseX = mouseX;
			m_mouseY = mouseY;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Input::IsTouchDevice()
	{
		return m_touchdevice;
	}

	bool Input::IsMousePressed(MouseButton key)
	{
		int b = 0;
		if (m_mouseState.rgbButtons[(int)key] & 0x80) { return true; }
		return false;
	}

}