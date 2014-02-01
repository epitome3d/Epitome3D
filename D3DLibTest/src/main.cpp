#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
				   , PSTR pScmdline, int iCmdshow)
{
	if (Initialize() == false) { return 0; }
	Run();
	Shutdown();

	return 0;
}

bool Initialize()
{
	bool result;
	int w, h;
	bool f;

	win = D3DLIB::Window::Window();
	if (!win.Initialize(L"D3DLib Test", false, false, 800, 600, true, false))
	{ return false; }
	win.GetWindowSize(w, h, f);

	s_tex.Initialize(win.d3d->GetDevice(), win.GetHWND());
	s_light.Initialize(win.d3d->GetDevice(), win.GetHWND());
	m_sphere.Initialize(win.d3d->GetDevice(), "assets/model/sphere.fbx", true);

	t_stars.Initialize(win.d3d->GetDevice(), L"assets/image/Stars.dds");
	t_earth.Initialize(win.d3d->GetDevice(), L"assets/image/Earth_CloudyDiffuse.dds");
	t_mouseon.Initialize(win.d3d->GetDevice(), L"assets/image/cursors/AccurateClick.dds");
	t_mouseoff.Initialize(win.d3d->GetDevice(), L"assets/image/cursors/Accurate.dds");

	cursor.Initialize(win.d3d->GetDevice(), 32, 32);
	stars.Initialize(win.d3d->GetDevice(), w, h);

	win.d3d->TurnZBufferOn();
	win.d3d->TurnOnAlphaBlending();

	return true;
}

void Shutdown()
{
	m_sphere.Shutdown();
	s_tex.Shutdown();
	s_light.Shutdown();

	t_stars.Shutdown();
	t_earth.Shutdown();
	t_mouseon.Shutdown();
	t_mouseoff.Shutdown();

	cursor.Shutdown();
	stars.Shutdown();

	win.Shutdown();
	return;
}

void Run()
{
	int w, h;
	bool f;
	HRESULT result;
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXMATRIX ortho;
	
	D3DXVECTOR4 l_ambientColor;
	D3DXVECTOR4 l_diffuseColor;
	D3DXVECTOR3 l_direction;
	D3DXVECTOR4 l_specularColor;
	float l_specularPower;
	
	l_ambientColor = D3DXVECTOR4(0.15f, 0.15f, 0.15f, 1.0f);
	l_diffuseColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	l_direction = D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	l_specularColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	l_specularPower = 4.0f;
	
	//LIGHT DIR  :  Changes  :  Which Dir?
	//front = 0,0,1 (inc, dec) (z)
	//left = 1,0,0  (dec, dec) (x)
	//back = 0,0,-1 (dec, inc) (z)
	//right = -1,0,0(inc, inc) (x)

	win.GetWindowSize(w, h, f);
	int m = w;
	if (h < w) { m = h; }
	int x = 1;
	float deg = 0.0f;

	win.input->SetMouseLocation(w/2, h/2);

	while (true)
	{
		/*** FRAME INITIALIZATION ***/

		//a return aborts the app
		if (win.Run(true) == false) { return; }
		if (win.input->IsKeyPressed(DIK_ESCAPE) == true) { return; }	
		if (win.HasFocus() == false)
		{
			while (win.HasFocus() == false)
			{				
				if (win.Run(true) == false)	{ return; }
			}
		}

		Movement();

		win.d3d->TurnZBufferOn();
		win.d3d->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);
		win.camera->SetPosition(movementX, rotationZ, movementZ - 15.0f);
		win.camera->SetRotation(rotationX, rotationY, 0.0f);
		win.camera->Render();
		win.camera->GetViewMatrix(view);
		win.d3d->GetWorldMatrix(world);
		win.d3d->GetOrthoMatrix(ortho);
		win.d3d->GetProjectionMatrix(projection);
		win.frustum->ConstructFrustum(SCREEN_DEPTH, projection, view);
		win.viewport->SetViewport(win.d3d->GetDeviceContext(), (float)w, (float)h, 0.0f, 1.0f, 0.0f, 0.0f);

		/*** MATH ***/

		deg = deg + (float)0.01;
		if (deg >= 360.0f) { deg -= 360.0f;}

		/***** DRAWING *****/
		
		win.painter->ClearList();

		//earth
		s_light.SetParameters(t_earth.GetTexture(), l_direction, l_ambientColor, l_diffuseColor,
			win.camera->GetPosition(), l_specularColor, l_specularPower);
		win.painter->AddToFront(ModelType(&m_sphere, &s_light, 
			new Transform(D3DXVECTOR3(deg, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			new CullAuto(), new PaintData(&world, &view, &projection, &ortho, &win.viewport->GetViewport())));

		//mouse
		if (mouseEnabled)
		{
			if (mousePressed)
			{
				s_tex.SetParameters(t_mouseon.GetTexture());
			}
			else
			{
				s_tex.SetParameters(t_mouseoff.GetTexture());
			}

			win.painter->AddToFront(BitmapType(&cursor, &s_tex, new Transform(), mouseX, mouseY, cursor.GetBitmapHeight(), cursor.GetBitmapWidth(), 0.0f, true,
				new PaintData(&world, &view, &projection, &ortho, &win.viewport->GetViewport())));
		}

		win.painter->Render(win.d3d, win.frustum, win.viewport, world, view, projection, ortho);
		
		DrawInfo();
		win.d3d->EndScene();
	}
}

void DrawInfo()
{
	WCHAR tempString[80];
	if(mouseEnabled)
	{
		swprintf_s(tempString, L"%d", mouseX);
		WCHAR mouseString[80];
		wcscpy_s (mouseString,L"Mouse X: ");
		wcscat_s (mouseString,tempString);

		win.text->Render(win.d3d->GetDeviceContext(), mouseString, L"Segoe UI", 10, 40, 12.0f, 0xffffffff,
			FW1_LEFT | FW1_TOP | FW1_RESTORESTATE );

		WCHAR mouseString2[80];
		swprintf_s(tempString, L"%d", mouseY);
		wcscpy_s (mouseString2,L"Mouse Y: ");
		wcscat_s (mouseString2,tempString);

		win.text->Render(win.d3d->GetDeviceContext(), mouseString2, L"Segoe UI", 10, 55, 12.0f, 0xffffffff,
			FW1_LEFT | FW1_TOP | FW1_RESTORESTATE );
	}
	else
	{
		win.text->Render(win.d3d->GetDeviceContext(), L"No mouse input.", L"Segoe UI", 10, 40, 12.0f, 0xbb00ff00,
			FW1_LEFT | FW1_TOP | FW1_RESTORESTATE );
	}

	WCHAR fpsString[80];
	swprintf_s(tempString, L"%d", win.GetFPS());
	wcscpy_s (fpsString,L"FPS: ");
	wcscat_s (fpsString,tempString);
	win.text->Render(win.d3d->GetDeviceContext(), fpsString, L"Segoe UI", 10, 10, 12.0f, 0xffffffff,
		FW1_LEFT | FW1_TOP | FW1_RESTORESTATE );
		
	WCHAR cpuString[80];
	swprintf_s(tempString, L"%d", win.GetCPU());
	wcscpy_s (cpuString,L"CPU: ");
	wcscat_s (cpuString,tempString);
	wcscat_s (cpuString,L"%");

	win.text->Render(win.d3d->GetDeviceContext(), cpuString, L"Segoe UI", 10, 25, 12.0f, 0xffffffff,
		FW1_LEFT | FW1_TOP | FW1_RESTORESTATE );
}

void Movement()
{
	frameTime = win.GetTime();
	mouseEnabled = win.input->GetMouseLocation(mouseX, mouseY);

	/*ScrollMove(DIK_LEFT, leftTurnSpeed, rotationY, frameTime, true, false);
	ScrollMove(DIK_RIGHT, rightTurnSpeed, rotationY, frameTime, false, false);
	ScrollMove(DIK_DOWN, downTurnSpeed, rotationX, frameTime, false, false);
	ScrollMove(DIK_UP, upTurnSpeed, rotationX, frameTime, true, false);*/
	ScrollMove(DIK_A, moveL, movementX, frameTime, true, true);
	ScrollMove(DIK_D, moveR, movementX, frameTime, false, true);
	ScrollMove(DIK_S, moveD, movementZ, frameTime, false, true);
	ScrollMove(DIK_W, moveUP, movementZ, frameTime, true, true);
	ScrollMove(DIK_PGUP, rotUSpeed, rotationZ, frameTime, true, true);
	ScrollMove(DIK_PGDN, rotDSpeed, rotationZ, frameTime, false, true);

	if (mouseEnabled)
	{
		if (win.input->IsMousePressed(Input::MouseButton::left))
		{
			if (mousePressed == false)
			{
				originalX = mouseX;
				originalY = mouseY;
				rotXo = -rotationY;
				rotYo = -rotationX;
				mousePressed = true;
			}
			else
			{
				float dX, dY;
				dX = (float)mouseX - (float)originalX;
				dY = (float)mouseY - (float)originalY;
				rotationY += -(dX / 25);
				rotationX += -(dY / 25);
				originalX = mouseX;
				originalY = mouseY;
			}
		}
		else
		{
			mousePressed = false;
		}
	}

	if (win.input->IsKeyPressed(DIK_R) == true)
	{
		rotationX = 0.0f;
		rotationY = 0.0f;
		movementX = 0.0f;
		movementZ = 0.0f;
		rotationZ = 0.0f;
	}
}

void ScrollMove(unsigned char DIK, float &directionSpeedVar, float &outputVar,
				float frameTime, bool positive, bool allowNegatives)
{
	if (win.input->IsKeyPressed(DIK) == true)
	{			
		directionSpeedVar += frameTime * 0.01f;

		if(directionSpeedVar > (frameTime * 0.15f))
		{
			directionSpeedVar = frameTime * 0.15f;
		}
	}
	else
	{
		directionSpeedVar -= frameTime * 0.005f;

		if(directionSpeedVar < 0.0f)
		{
			directionSpeedVar = 0.0f;
		}
	}

	if (!positive) {outputVar -= directionSpeedVar;} else {outputVar += directionSpeedVar;}
	if ((outputVar < 0.0f) && (!allowNegatives))
	{
		outputVar += 360.0f;
	}
}