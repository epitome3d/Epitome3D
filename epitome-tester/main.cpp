#include <epitome-core.h>
#include <iostream>
using namespace EPITOME;

#define window_width 640
#define window_height 480

//Initialize OpenGL perspective matrix
void Setup(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)width / height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
}

static void Key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static void ErrorFn(int error, const char* description)
{
	fputs(description, stderr);
}

Window Init()
{
	//create window
	Window window(window_width, window_height, "Epitome3D Demo");

	//set key callbacks
	//TODO eventually abstract this to the Keyboard and use a frame-based system
	//TODO User asks if the key is equal whenever they want, frm the Keyboard
	//TODO keys are specific to the window
	window.setKeyHandler(Key);

	//get window size
	auto size = window.getSize();

	Setup(size.width, size.height);

	return window;
}

void Loop(Window window)
{
	while (!window.shouldClose())
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
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex3f(mPos.x-2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y-2, -50);
		glVertex3f(mPos.x+2, mPos.y+2, -50);
		glVertex3f(mPos.x-2, mPos.y+2, -50);
		glEnd();
		// Swap buffers (color buffers, makes previous render visible)
		window.swapBuffers();
		// Increase angle to rotate
		angle += 0.25;

		//checks for events
		glfwPollEvents();
	}
}

int main(int argc, char** argv)
{
	Initialize();

	Window window = Init();
	Loop(window);
	Exit();
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