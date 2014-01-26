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
	sound1 = 0;
	buffer1 = 0;
	bool result;
	int w, h;
	bool f;

	win = D3DLIB::Window::Window();
	if (!win.Initialize(L"D3DLib Test", false, false, 800, 600, true, false))
	{ return false; }

	win.GetWindowSize(w, h, f);
	win.d3d->TurnZBufferOn();
	win.d3d->TurnOnAlphaBlending();

	//initialize the sound1 object
	sound1 = new D3DLIB::Sound_WAVEPCM;
	if (!sound1) { return false; }
	result = sound1->Initialize(win.GetHWND());
	if(!result)	{ return false;	}
	result = sound1->LoadFile(&buffer1, "../assets/sound/sound01.wav");
	if (!result) { return false; }
	result = sound1->Play(buffer1, false);
	if (!result) { return false; }

	//initialize the bitmap object
	image1 = new Bitmap();
	image1->Initialize(win.d3d->GetDevice(), w, h);

	cursor = new Bitmap();
	cursor->Initialize(win.d3d->GetDevice(), w, h);

	//initialize models
	earth = new Model();
	earth->Initialize(win.d3d->GetDevice(), "../assets/model/Earth.txt", true);
	moon = new Model();
	moon->Initialize(win.d3d->GetDevice(), "../assets/model/Sphere.txt", true);

	//initialize shaders
	shade_tex = new Shader_TEXTURE();
	shade_tex->Initialize(win.d3d->GetDevice(), win.GetHWND());
	shade_light = new Shader_LIGHT();
	shade_light->Initialize(win.d3d->GetDevice(), win.GetHWND());

	//initialize textures
	texhill = new Texture(win.d3d->GetDevice(), L"../assets/image/CheckerboardHill.dds");
	texgrass = new Texture(win.d3d->GetDevice(), L"../assets/image/CheckerboardGrass.dds");
	texteapot = new Texture(win.d3d->GetDevice(), L"../assets/image/Teapot.dds");
	texearth = new Texture(win.d3d->GetDevice(), L"../assets/image/Earth_CloudyDiffuse.dds");
	texmoon = new Texture(win.d3d->GetDevice(), L"../assets/image/Moon.dds");
	texstars = new Texture(win.d3d->GetDevice(), L"../assets/image/stars-04.dds");
	texmouse = new Texture(win.d3d->GetDevice(), L"../assets/image/Cursors/Accurate.dds");
	texmouseclick = new Texture(win.d3d->GetDevice(), L"../assets/image/Cursors/Accurate Click.dds");
	return true;
}

void Shutdown()
{
	sound1->ShutdownBuffer(&buffer1);
	sound1->Shutdown();
	image1->Shutdown();
	cursor->Shutdown();

	texhill->Shutdown();
	texgrass->Shutdown();
	texteapot->Shutdown();
	texearth->Shutdown();
	texstars->Shutdown();
	texmoon->Shutdown();
	texmouse->Shutdown();
	texmouseclick->Shutdown();

	earth->Shutdown();
	moon->Shutdown();

	shade_tex->Shutdown();
	shade_light->Shutdown();
	win.Shutdown();
	return;
}

void Run()
{
	int w, h;
	bool f;
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
		//a return aborts the app
		if (win.Run(true) == false) { return; }
		if (win.input->IsKeyPressed(DIK_ESCAPE) == true) { return; }	
		if (win.HasFocus() == false)
		{
			sound1->Pause(buffer1);
			while (win.HasFocus() == false)
			{				
				if (win.Run(true) == false)	{ return; }
			}
			sound1->Play(buffer1, false);
		}

		Movement();

		win.d3d->TurnZBufferOn();
		win.d3d->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);
		win.camera->SetPosition(0.0f, 0.0f, -30.0f);
		win.camera->SetRotation(0.0f, 0.0f, 0.0f);
		win.camera->Render();
		win.camera->GetViewMatrix(view);
		win.d3d->GetWorldMatrix(world);
		win.d3d->GetOrthoMatrix(ortho);
		win.d3d->GetProjectionMatrix(projection);
		win.frustum->ConstructFrustum(SCREEN_DEPTH, projection, view);
		win.viewport->SetViewport(win.d3d->GetDeviceContext(), (float)w, (float)h, 0.0f, 1.0f, 0.0f, 0.0f);

		deg = deg + (float)0.01;
		if (deg >= 360.0f) { deg -= 360.0f;}

		/***** DRAWING *****/
		
		win.painter->ClearList();		

		//background stars
		shade_tex->SetParameters(texstars->GetTexture());
		win.painter->AddToFront(BitmapType(image1, (Shader*)shade_tex, new Transform(),
			0, 0, w, h, 0.0f, true, new PaintData(&world, &view, &projection, &ortho, &win.viewport->GetViewport())));

		win.camera->SetRotation(rotationX, rotationY, 0.0f);
		win.camera->SetPosition(movementX, rotationZ, -30.0f + movementZ);
		win.camera->Render();
		win.camera->GetViewMatrix(view);
		
		//moon
		shade_tex->SetParameters(texmoon->GetTexture());
		win.painter->AddToFront(ModelType(moon, (Shader*)shade_tex, new Transform(
			D3DXVECTOR3(deg / 28, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 
			D3DXVECTOR3(-6.0f, 0.0f, -75.0f)), new CullAuto(), new PaintData(
			&world, &view, &projection, &ortho, &win.viewport->GetViewport())));

		//earth
		shade_light->SetParameters(texearth->GetTexture(), l_direction,
			l_ambientColor, l_diffuseColor, win.camera->GetPosition(),
			l_specularColor, l_specularPower);
		win.painter->AddToFront(ModelType(moon, (Shader*)shade_light, new Transform(
			D3DXVECTOR3(deg, 0.0f, 0.0f), D3DXVECTOR3(3.66f, 3.66f, 3.66f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)), new CullAuto(),
			new PaintData(&world, &view, &projection, &ortho,
			&win.viewport->GetViewport())));
		
		win.camera->SetRotation(0.0f, 0.0f, 0.0f);
		win.camera->SetPosition(0.0f, 0.0f, -30.0f);
		win.camera->Render();
		win.camera->GetViewMatrix(view);
		
		/*win.painter->AddToFront(TextType(win.text, L"Hello World!", L"Segoe UI",
			(float)(w/2), (float)h/2, 60.0f, 0xffffffff, 
			FW1_CENTER | FW1_VCENTER | FW1_RESTORESTATE,
			new PaintData(&world, &view, &projection, &ortho,
			&win.viewport->GetViewport())));*/

		//pointer
		if (mouseEnabled) {
		if (mousePressed)
		{
			shade_tex->SetParameters(texmouseclick->GetTexture());
		}
		else
		{
			shade_tex->SetParameters(texmouse->GetTexture());
		}		

		win.painter->AddToFront(BitmapType(cursor, (Shader*)shade_tex, new Transform(),
			mouseX, mouseY, 32, 32, 0, true, new PaintData(&world, &view, &projection, &ortho,
			&win.viewport->GetViewport()))); }

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