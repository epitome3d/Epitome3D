#ifndef D3DLIB_WINDOW
#define D3DLIB_WINDOW

//PRE-PROCESSOR DIRECTIVES
#define WIN32_LEAN_AND_MEAN

//INCLUDES
#include <Windows.h>
#include "globals.h"
#include "input.h"
#include "D3D.h"
#include "sound.h"
#include "text.h"
#include "camera.h"
#include "timer.h"
#include "fps.h"
#include "cpu.h"
#include "painter.h"
#include "frustum.h"

//unused includes
#include "bitmap.h"
#include "model.h"

namespace D3DLIB
{
	class Window
	{
	public:
		Window();
		Window(const Window&);
		~Window();

		bool Initialize(LPCWSTR title, bool showcursor, bool fullscreen,
			int windowedwidth, int windowedheight, bool vsync, bool bindMouse);
		void Shutdown();
		bool Frame();
		bool Run(bool allowexit);

		void ShowError(LPCWSTR string, LPCWSTR title);
		void Cursor(bool visible);
		void GetWindowSize(int& width, int& height, bool& fullscreen);
		HWND GetHWND();
		float GetTime();
		int GetFPS();
		int GetCPU();
		bool HasFocus();

		Input* input;
		D3D* d3d;
		Sound* sound;
		Text* text;
		Camera* camera;
		Painter* painter;
		Frustum* frustum;
		Viewport* viewport;

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		void InitializeWindows(int&, int&, LPCWSTR);
		void ShutdownWindows();

		Timer* timer;
		FPS* fps;
		CPU* cpu;

		LPCWSTR m_applicationName;
		HINSTANCE m_hinstance;
		HWND m_hwnd;
		int m_screenwidth, m_screenheight;
		bool m_focus;
	};

	//function prototypes
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	//globals
	static Window* ApplicationHandle = 0;
}

#endif