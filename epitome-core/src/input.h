#ifndef EPITOME_INPUT
#define EPITOME_INPUT

//preprocessor directives
#define DIRECTINPUT_VERSION 0x0800

//linking
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//includes
#include <dinput.h>

namespace EPITOME
{
	class Input
	{
	public:
		enum MouseButton
		{
			left, middle, right, key_4
		};

		Input();
		Input(const Input&);
		~Input();

		bool Initialize(HINSTANCE, HWND, int, int, bool);
		void Shutdown();
		bool Frame(bool &lost);

		bool GetMouseLocation(int&, int&);
		bool SetMouseLocation(int, int);
		bool IsKeyPressed(unsigned char DIK);

		bool IsTouchDevice();
		bool IsMousePressed(MouseButton key);

	private:
		bool ReadKeyboard(bool &lost);
		bool ReadMouse();
		void ProcessInput();

		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_keyboard;
		IDirectInputDevice8* m_mouse;
		unsigned char m_keyboardState[256];
		DIMOUSESTATE m_mouseState;

		int m_screenWidth, m_screenHeight;
		int m_mouseX, m_mouseY;
		int m_desktopWidth, m_desktopHeight;
		int m_windowX, m_windowY;
		bool m_touchdevice;
	};
}

#endif