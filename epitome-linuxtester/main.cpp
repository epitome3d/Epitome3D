#include <GL/freeglut.h>
#include <iostream>

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

void Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");
	glutIdleFunc(Render);
	glutDisplayFunc(Blank);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	Setup(window_width, window_height);
}

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#include <shellapi.h>
#pragma comment(linker, "/SUBSYSTEM:WINDOWS") //enable non-shell mode
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	LPWSTR *szArglist;
	int nArgs;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	Init(nArgs, (char**)szArglist);
	glutMainLoop();

	return 0;
}
#endif

#ifdef LINUX
int main(int argc, char** argv)
{
	Init(argc, argv);
	glutMainLoop();

	return 0;
}
#endif