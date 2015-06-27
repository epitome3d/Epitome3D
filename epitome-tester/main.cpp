#include <epitome-core.h>
#include <iostream>
using namespace EPITOME;

#define window_width 640
#define window_height 480

Window* mainwindow;
Window* secondwindow;

//Initialize OpenGL perspective matrix
void Setup(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)width / height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
}

static void E3DKey(Window& win, Keys key, KeyState state)
{
	if (key == KEY_ESCAPE && state == KEYS_RELEASED) //this is in case we throw more keys in this loop
		mainwindow->close();
	if (key == KEY_ESCAPE && state == KEYS_PRESSED)
		secondwindow->close();
}

static void ErrorFn(int error, const char* description)
{
	fputs(description, stderr);
}

static void ResizeFn(Window& win, Size<int> s)
{
	MessageBox(NULL, "Second onResize!", "ANOTHER", MB_OK);
	return;
}

void Init()
{
	//create window
	mainwindow = new Window(window_width, window_height, "Epitome3D Demo");
	//mainwindow->onResize(ResizeFn);

	secondwindow = new Window(window_width, window_height, "Epitome3D Demo - SECOND Window");
	secondwindow->onResize(ResizeFn);

	mainwindow->beginDraw();

	mainwindow->onResize([](Window& win, Size<int> s) {
#ifdef WINDOWS
		MessageBox(NULL, "Hey!", "Cool beans!", MB_OK);
#else
		std::cout << "I'm preventing you from resizing any faster than incrementally! \
Oh wait, just kidding, there's no MessageBox in your way in this version. \
But there is something better: VSync!" << std::endl;
#endif
	});

	//TODO onClose does not fire when closed using ESCAPE key
	mainwindow->onClose([](Window& win) {
#ifdef WINDOWS
		//TODO abstract Messagebox to Dialog
		MessageBox(NULL, "Yikes! I'm shutting down!", "Noooo!", MB_OK);
#else
		std::cout << "Gotta close fast!" << std::endl;
#endif
	});
	//set key callbacks
	//TODO keys are specific to the window?
	//window.setKeyHandler(Key);
	secondwindow->keyboard->onKeyPressed(KEY_ESCAPE, E3DKey);
	secondwindow->keyboard->onKeyReleased(KEY_ESCAPE, E3DKey);

	//get window size
	auto size = mainwindow->getSize();

	Setup(size.width, size.height);
}

void Loop()
{
	while (!mainwindow->isClosing())
	{
		//keep running
		// Z angle
		static float angle;
		// Clear color (screen)
		// And depth (used internally to block obstructed objects)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// BEGIN OLD CODE (to be reimplemented once demo viewed)
		/*//Load identity matrix
		glLoadIdentity();
		// Multiply in translation matrix
		glTranslatef(0, 0, -10);
		// Multiply in rotation matrix
		glRotatef(angle, 0, 0, 1);
		// Render colored quad
		glBegin(GL_QUADS);
		glColor3ub(255, 000, 000); glVertex2f(-1, 1);
		glColor3ub(000, 255, 000); glVertex2f(1, 1);
		glColor3ub(000, 000, 255); glVertex2f(1, -1);
		glColor3ub(255, 255, 000); glVertex2f(-1, -1);
		glEnd();*/
		// END OLD CODE

		// Inefficient/sloppy at the moment, for demonstration purposes

		Point<double> mPos = EPITOME::Mouse::getMousePosition(mainwindow);
		mPos.x = (mPos.x - 320) / 12;
		mPos.y = (-mPos.y + 230) / 12;
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat b = (mainwindow->keyboard->isKeyDown(Keys::KEY_SPACE)) ? 1.0f : 0.0f;

		glColor3f(0.0, 1.0, b);
		glBegin(GL_POLYGON);
		glVertex3f(mPos.x-2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y+2, -50);
		glVertex3f(mPos.x-2, mPos.y+2, -50);
		glEnd();
		// Swap buffers (color buffers, makes previous render visible)
		if (!mainwindow->isClosing())
		{
			mainwindow->Render();
		}
		if (!secondwindow->isClosing())
		{
			secondwindow->Render();
		}
		// Increase angle to rotate
		angle += 0.25;

		//checks for events
		Update();
	}
}

void Dispose()
{
	delete mainwindow; //will call the destructor and the Dispose() method
	delete secondwindow;
}

int main(int argc, char** argv)
{
	EPITOME::Initialize();

	Init();
	Loop();
	Dispose();

	EPITOME::Exit();
}

#ifdef WINDOWS
#include <windows.h>
#include <shellapi.h>
#pragma comment(linker, "/subsystem:windows")
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	LPWSTR *szArglist;
	int argc;
	char** argv;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
	argv = (char**)szArglist;

	main(argc, argv);
}

#endif