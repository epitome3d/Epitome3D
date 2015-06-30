#include <epitome-core.h>
#include <iostream>
#include <thread>
using namespace EPITOME;

#define window_width 640
#define window_height 480

static bool running = true;

static void E3DKey(Window& win, Keys key, KeyState state)
{
	if (key == KEY_ESCAPE && state == KEYS_RELEASED) //this is in case we throw more keys in this loop
		win.close();
}

static void ErrorFn(int error, const char* description)
{
	fputs(description, stderr);
}

static void ThreadLoop(Window* window)
{
	//set a few events
	window->keyboard->onKeyReleased(Keys::KEY_ESCAPE, E3DKey);

	auto size = window->getBufferSize();
	window->beginDraw();

	glViewport(0, 0, size.width, size.height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)size.width / (float)size.height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
	glfwSwapInterval(1);

	while (running)
	{
		if (window->isClosing())
			running = false;

		//keep running
		// Z angle
		static float angle;
		// Clear color (screen)
		// And depth (used internally to block obstructed objects)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// BEGIN OLD CODE
		//Load identity matrix
		/*glLoadIdentity();
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

		//TODO Inefficient/sloppy at the moment, for demonstration purposes

		Point<double> mPos = window->mouse->getPosition();
		//TODO why???
		mPos.x = (mPos.x - 320) / 12;
		mPos.y = (-mPos.y + 230) / 12;

		GLfloat b = (window->keyboard->isKeyDown(Keys::KEY_SPACE)) ? 1.0f : 0.0f;

		glColor3f(0.0, 1.0, b);
		glBegin(GL_POLYGON);
		glVertex3f(mPos.x-2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y+2, -50);
		glVertex3f(mPos.x-2, mPos.y+2, -50);
		glEnd();

		// Swap buffers (color buffers, makes previous render visible)
		window->render();

		// Increase angle to rotate
		angle += 0.25;

		//checks for events
		Update();
	}
	glfwMakeContextCurrent(NULL);
	running = false;
}

void Run()
{
	Window* mainwindow = new Window(window_width, window_height, "Epitome3D Demo");
	mainwindow->setPosition(100, 100);
	mainwindow->show();
	Window* secondwindow = new Window(window_width, window_height, "Epitome3D Demo - SECOND WINDOW");
	secondwindow->show();
	secondwindow->setPosition(170 + window_width, 100);

	thread w1(ThreadLoop, mainwindow);
	thread w2(ThreadLoop, secondwindow);

	while (running)
	{
		glfwWaitEvents();
	}

	mainwindow->hide();
	secondwindow->hide();

	w1.join();
	w2.join();

	delete mainwindow; //will call the destructor and the dispose() method
	delete secondwindow;
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