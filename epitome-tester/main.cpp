#include <epitome-core.h>
#include <iostream>
#include <thread>
using namespace EPITOME;

#define window_width 640
#define window_height 480

static bool running = true;

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
		win.close();
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

static void ThreadLoop(Window* window)
{
	auto size = window->getSize();
	window->beginDraw();

	glViewport(0, 0, size.width, size.height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)size.width / (float)size.height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
	glfwSwapInterval(1);

	while (running)
	{
		//keep running
		// Z angle
		static float angle;
		// Clear color (screen)
		// And depth (used internally to block obstructed objects)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// BEGIN OLD CODE (to be reimplemented once demo viewed)
		//Load identity matrix
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
		glEnd();
		// END OLD CODE

		//TODO Inefficient/sloppy at the moment, for demonstration purposes

		/*Point<double> mPos = window->mouse->getPosition();
		mPos.x = (mPos.x - 320) / 12;
		mPos.y = (-mPos.y + 230) / 12;
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat b = (window->keyboard->isKeyDown(Keys::KEY_SPACE)) ? 1.0f : 0.0f;

		glColor3f(0.0, 1.0, b);
		glBegin(GL_POLYGON);
		glVertex3f(mPos.x-2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y+2, -50);
		glVertex3f(mPos.x-2, mPos.y+2, -50);
		glEnd();*/

		// Swap buffers (color buffers, makes previous render visible)
		window->Render();

		// Increase angle to rotate
		angle += 0.25;

		//checks for events
		Update();

		if (window->isClosing())
			running = false;
	}
	glfwMakeContextCurrent(NULL);
	running = false;
}

void Run()
{
	Window* mainwindow = new Window(window_width, window_height, "Epitome3D Demo");
	mainwindow->keyboard->onKeyReleased(Keys::KEY_ESCAPE, E3DKey);
	glfwShowWindow(mainwindow->getHandle());
	//Window* secondwindow = new Window(window_width, window_height, "Epitome3D Demo - SECOND WINDOW");

	thread w1(ThreadLoop, mainwindow);
	//thread w2(ThreadLoop, secondwindow);
	
	//ThreadLoop(mainwindow);

	while (running)
	{
		glfwWaitEvents();
	}

	glfwHideWindow(mainwindow->getHandle());
	//glfwHideWindow(secondwindow->getHandle());

	w1.join();
	//w2.join();

	delete mainwindow; //will call the destructor and the Dispose() method
	//delete secondwindow;
}

int main(int argc, char** argv)
{
	EPITOME::Initialize();

	Run();

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