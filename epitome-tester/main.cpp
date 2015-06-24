#include <epitome-core.h>
#include <iostream>
using namespace EPITOME;

#define window_width 640
#define window_height 480

Window* mainwindow;

//Initialize OpenGL perspective matrix
void Setup(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)width / height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
}

static void E3DKey(Keys key, KeyState state)
{
	if (key == KEY_ESCAPE && state == KEYS_PRESSED)
		mainwindow->close();
}

static void ErrorFn(int error, const char* description)
{
	fputs(description, stderr);
}

void Init()
{
	//create window
	mainwindow = new Window(window_width, window_height, "Epitome3D Demo");

	//set key callbacks
	//TODO keys are specific to the window?
	//window.setKeyHandler(Key);
	Keyboard::onKeyReleased(KEY_ESCAPE, E3DKey);

	//get window size
	auto size = mainwindow->getSize();

	Setup(size.width, size.height);
}

void Loop()
{
	while (!mainwindow->shouldClose())
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

		Point<double> mPos = EPITOME::Mouse::getMousePosition();
		mPos.x = (mPos.x - 320) / 12;
		mPos.y = (-mPos.y + 230) / 12;
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat b = (Keyboard::isKeyDown(Keys::KEY_SPACE)) ? 1.0f : 0.0f;

		glColor3f(0.0, 1.0, b);
		glBegin(GL_POLYGON);
		glVertex3f(mPos.x-2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y+2, -50);
		glVertex3f(mPos.x-2, mPos.y+2, -50);
		glEnd();
		// Swap buffers (color buffers, makes previous render visible)
		mainwindow->swapBuffers();
		// Increase angle to rotate
		angle += 0.25;

		//checks for events
		Update();
	}
}

void Dispose()
{
	delete mainwindow; //will call the destructor and the Dispose() method
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