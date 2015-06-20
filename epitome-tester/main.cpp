#include <epitome-core.h>
#include <iostream>
using namespace EPITOME;

//#pragma comment(lib, "freeglut.lib")
//#pragma comment(lib, "freeglutd.lib")

#define window_width 640
#define window_height 480

// Initialize OpenGL perspective matrix
void Setup(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)width / height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void Render()
{
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
	glutSwapBuffers();
	// Increase angle to rotate
	angle += 0.25;
}

void Blank() { }

void Init()
{
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");
	glutIdleFunc(Render);
	glutDisplayFunc(Blank);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	Setup(window_width, window_height);
}

#ifdef WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	EPITOME::Initialize();
	Init();
	glutMainLoop();
	EPITOME::Exit();

	return 0;
}
#endif

#ifdef LINUX
int main(int argc, char** argv)
{
	EPITOME::Initialize(argc, argv);
	Init();
	glutMainLoop();

	return 0;
}
#endif