//#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

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

GLFWwindow* Init()
{
	//create window
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Tutorial 01", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//set key callbacks
	glfwSetKeyCallback(window, Key);

	//get window size
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	Setup(width, height);

	return window;
}

void Loop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		//keep running
		// Z angle
		static float angle;
		// Clear color (screen)
		// And depth (used internally to block obstructed objects)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Load identity matrix
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
		// Swap buffers (color buffers, makes previous render visible)
		glfwSwapBuffers(window);
		// Increase angle to rotate
		angle += 0.25;

		//checks for events
		glfwPollEvents();
	}
}

#ifdef WINDOWS
#include <windows.h>
#include <shellapi.h>
#pragma comment(linker, "/subsystem:windows")
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Initialize();

	LPWSTR *szArglist;
	int argc;
	char** argv;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
	argv = (char**)szArglist;

	GLFWwindow* window = Init();
	Loop(window);
	glfwTerminate();
	return 0;
}

#else

int main(int argc, char** argv)
{
	Initialize();

	GLFWwindow* window = Init();
	Loop(window);
	glfwTerminate();
	return 0;
}
#endif