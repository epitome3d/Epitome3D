#include "window.h"

namespace D3DLIB
{
	Window::Window()
	{
		input = 0;
		d3d = 0;
		sound = 0;
		text = 0;
		camera = 0;
		timer = 0;
		fps = 0;
		cpu = 0;
		painter = 0;
		frustum = 0;
		viewport = 0;

		m_focus = false;
	}
	Window::Window(const Window& other)
	{
	}
	Window::~Window()
	{
	}
	
	bool Window::Initialize(LPCWSTR title, bool showcursor, bool fullscreen,
			int windowedwidth, int windowedheight, bool vsync, bool bindMouse)
	{
		int screenWidth, screenHeight;
		bool result;

		//initilize the size of the screen
		screenWidth = 0;
		screenHeight = 0;

		SHOW_CURSOR = showcursor;
		FULL_SCREEN = fullscreen;
		WINDOWED_WIDTH = windowedwidth;
		WINDOWED_HEIGTH = windowedheight;
		VSYNC_ENABLED = vsync;
		
		//Initialize the Windows API
		InitializeWindows(screenWidth, screenHeight, title);

		// Initialize the Direct3D object.
		d3d = new D3D;
		if(!d3d)
		{
			return false;
		}
		result = d3d->Initialize(screenWidth, screenHeight, VSYNC_ENABLED,
			m_hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
		if(!result)
		{
			MessageBox(m_hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
			return false;
		}
		
		//Initialize the input object
		input = new Input;
		if(!input)
		{
			return false;
		}
		result = input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight, bindMouse);
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize DirectInput.", L"Error", MB_OK);
			return false;
		}

		//Initialize the viewport
		D3D11_VIEWPORT* vp = new D3D11_VIEWPORT();
		UINT i = 1;
		d3d->GetDeviceContext()->RSGetViewports(&i, vp);
		viewport = new Viewport(d3d->GetDeviceContext(), *vp);
		
		//Create the text class
		text = new Text;
		if(!text)
		{
			return false;
		}	
		result = text->Initialize(d3d->GetDevice(), d3d->GetDeviceContext());
		if (!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
			return false;
		}

		//Initialize the camera
		camera = new Camera;
		if(!camera)
		{
			return false;
		}
		camera->SetPosition(0.0f, 1.0f, -10.0f);

		//Initialize the timer
		timer = new Timer;
		if(!timer) { return false; }
		result = timer->Initialize();
		if(!result)
		{
			MessageBox(m_hwnd, L"Could not initialize the timer.", L"Error", MB_OK);
			return false;
		}

		//Initialize the FPS object
		fps = new FPS;
		if(!fps) { return false; }
		fps->Initialize();

		//Initialize the CPU object
		cpu = new CPU;
		if(!cpu) { return false; }
		cpu->Initialize();

		//Initialize the painter
		painter = new Painter();

		//Initialize the frustum
		frustum = new Frustum();

		m_focus = true;
		return true;
	}

	bool Window::Frame()
	{
		input->Frame(m_focus);
		m_focus = !m_focus;
		timer->Frame();
		fps->Frame(m_focus);
		cpu->Frame();
		return true;
	}

	bool Window::Run(bool allowexit)
	{
		MSG msg;

		//initialize the message structure
		ZeroMemory(&msg, sizeof(MSG));

		//loop until there is a quit message from the window or user

		//handle the windows messages
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//if windows signals to end the application then exit out
		if ((msg.message == WM_QUIT) && (allowexit == true))
		{
			return false;
		}
		else
		{
			//otherwise, process the frame
			if(Frame() == false)
			{
				return false;
			}
		}

		return true;
	}

	void Window::Shutdown()
	{
		if (input)
		{
			input->Shutdown();
			delete input;
			input = 0;
		}
		if (d3d)
		{
			d3d->Shutdown();
			delete d3d;
			d3d = 0;
		}
		if (sound)
		{
			sound->Shutdown();
			delete sound;
			sound = 0;
		}
		if (text)
		{
			text->Shutdown();
			delete text;
			text = 0;
		}
		if (camera)
		{
			delete camera;
			camera = 0;
		}
		if (timer)
		{
			delete timer;
			timer = 0;
		}
		if (fps)
		{
			delete fps;
			fps = 0;
		}
		if (cpu)
		{
			cpu->Shutdown();
			delete cpu;
			cpu = 0;
		}

		ShutdownWindows();
		return;
	}

	void Cursor(bool visible)
	{
		SHOW_CURSOR = visible;
		ShowCursor(visible);
	}

	void Window::InitializeWindows(int& screenWidth, int& screenHeight,
		LPCWSTR title)
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;

		//get external pointer to this object
		ApplicationHandle = this;

		//get instance of this application
		m_hinstance = GetModuleHandle(NULL);

		//give the application a name
		m_applicationName = title;

		//setup the windows class with the default settings
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);

		//register the window class
		RegisterClassEx(&wc);

		//determine the resolution of the clients desktop screen
		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);

		//setup the screen settings depending on 
		//whether it is running in fullscreen or not

		if (FULL_SCREEN)
		{
			//set the screen to the maximum size of the desktop
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			//change display settings to fullscreen
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		
			//set the window position
			posX = posY = 0;
		}
		else
		{
			//set to a 800x600 resolution
			screenWidth = WINDOWED_WIDTH;
			screenHeight = WINDOWED_HEIGTH;

			//place the window in the middle of the screen
			posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) /2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) /2;
		}

		//create the window and apply the settings to it
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName,
			m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

		m_screenwidth = screenWidth;
		m_screenheight = screenHeight;

		//bring the window up and set it as main focus
		ShowWindow(m_hwnd, SW_SHOW);
		SetForegroundWindow(m_hwnd);
		SetFocus(m_hwnd);

		//Hide the mouse cursor
		ShowCursor(SHOW_CURSOR);

		return;
	}

	void Window::ShutdownWindows()
	{
		//show the mouse cursor
		ShowCursor(true);

		//fix the display settings if leaving fullscreen mode
		if (FULL_SCREEN)
		{
			ChangeDisplaySettings(NULL, 0);
		}

		//remove the window
		DestroyWindow(m_hwnd);
		m_hwnd = NULL;

		//remove the application instance
		UnregisterClass(m_applicationName, m_hinstance);
		m_hinstance = NULL;

		//release the pointer to this class
		ApplicationHandle = NULL;

		return;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		switch(umessage)
		{
			//check if the window is being destroyed
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}

		default:
			{
				//all other messages pass onto the message handler
				return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
			}
		}
	}

	LRESULT CALLBACK Window::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}

	HWND Window::GetHWND()
	{
		return m_hwnd;
	}

	void Window::GetWindowSize(int& width, int& height, bool& fullscreen)
	{
		fullscreen = FULL_SCREEN;
		width = m_screenwidth;
		height = m_screenheight;
		return;
	}

	void Window::ShowError(LPCWSTR string, LPCWSTR title)
	{
		MessageBox(m_hwnd, string, title, MB_OK | MB_ICONERROR);
	}

	float Window::GetTime()
	{
		return timer->GetTime();
	}

	bool Window::HasFocus()
	{
		return m_focus;
	}

	int Window::GetFPS()
	{
		return fps->GetFPS();
	}

	int Window::GetCPU()
	{
		return cpu->GetCPUPercentage();
	}

} //namespace D3DLIB