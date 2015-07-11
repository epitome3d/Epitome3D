#include <epitome-core.h>
#include <iostream>
#include <thread>
using namespace EPITOME;

#define window_width 640
#define window_height 480

static bool running = true;
static bool enter_pressed = false;

static void E3DKey(Window& win, Keys key, KeyState state)
{
	if (key == KEY_ESCAPE && state == KEYS_RELEASED) //this is in case we throw more keys in this loop
		win.close();
	if (key == KEY_ENTER && state == KEYS_PRESSED)
		enter_pressed = true;
	if (key == KEY_ENTER && state == KEYS_RELEASED)
		enter_pressed = false;
}

static void ErrorFn(int error, const char* description)
{
	fputs(description, stderr);
}

static void onMouseMove(Window window, Point<double> m1)
{
	fprintf(stdout, "Mouse (%s): %i %i\r\n", window.getTitle(), (int)m1.x, (int)m1.y);
}

static void ThreadLoop(Window* window)
{
	//set a few events
	window->keyboard->onKeyReleased(Keys::KEY_ESCAPE, E3DKey);
	window->keyboard->onKeyPressed(KEY_ENTER, E3DKey);
	window->keyboard->onKeyReleased(KEY_ENTER, E3DKey);
	window->mouse->onMove(onMouseMove);

	auto size = window->getBufferSize();
	auto winsize = window->getWindowSize();
	window->beginDraw();

	/*glViewport(0, 0, size.width, size.height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)size.width / (float)size.height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
	glfwSwapInterval(1);*/

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, size.width - 1, size.height - 1, 0);
	// Here we use orthographic projection
	glPopMatrix();
	// Back to the projection we were using before
	glMatrixMode(GL_MODELVIEW);  // Best switch back to modelview

	glViewport(0, 0, size.width, size.height);
	glfwSwapInterval(1);

	GLdouble outx, outy, outz;
	GLdouble outx2, outy2, outz2;
	GLint viewport[4];
	GLdouble modelview[16], projection[16];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	while (running)
	{
		if (window->isClosing())
			running = false;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer (background)
		Point<double> mPos = window->mouse->getPosition();

		GLfloat b = (window->keyboard->isKeyDown(Keys::KEY_SPACE)) ? 1.0f : 0.0f;
		GLfloat r = (enter_pressed) ? 1.0f : 0.0f;

		//find the 40x40 pixel square, inverting the y axis
		gluUnProject(mPos.x-20, size.height-mPos.y-20, 0.0, modelview, projection, viewport, &outx, &outy, &outz);
		gluUnProject(mPos.x+20, size.height-mPos.y+20, 0.0, modelview, projection, viewport, &outx2, &outy2, &outz2);

		// Draw the square
		glBegin(GL_QUADS);
		glColor3f(b, 1.0f, r);
		glVertex2f(outx, outy);
		glVertex2f(outx2, outy);
		glVertex2f(outx2, outy2);
		glVertex2f(outx, outy2);
		glEnd();

		// Swap buffers (color buffers, makes previous render visible)
		window->render();

		// Increase angle to rotate
		//angle += 0.25;

		//checks for events
		Update();
	}
	glfwMakeContextCurrent(NULL);
	running = false;
}

GLuint loadBMP(const char * imagepath)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;
	// Open the file
	FILE * file = fopen(imagepath, "rb");
	if (!file) {
		return 0;
	}
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		// Not a correct BMP file
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		// Not a correct BMP file
		return 0;
	}
	
	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way
	
	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	// Bind to dummy texture beforehand
	glBindTexture(GL_TEXTURE_2D, 0);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	return textureID;
}

void DrawImage(const Size<int>& size, GLuint texture) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, size.width, 0.0, size.height, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 100, 0);
	glTexCoord2f(1, 1); glVertex3f(100, 100, 0);
	glTexCoord2f(1, 0); glVertex3f(100, 0, 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

}

static void ThirdLoop(Window& win)
{
	GLuint tex = loadBMP("cat.bmp");
	auto size = win.getWindowSize();
	win.beginDraw();
	while (running)
	{
		if (win.isClosing())
			running = false;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer (background)

		DrawImage(size, tex);
		win.render();

		Update();
	}
}

void Run()
{
	//Get display information
	Display primaryDisplay = Displays::getPrimary();
	Size<int> displaySize = primaryDisplay.getPhysicalSize();
	VideoMode videoMode = primaryDisplay.getBestVideoMode();

	//create a placebo window, then create a fullscreen window with the full properties
	Window* mainwindow = new Window(videoMode.getSize().width, videoMode.getSize().height, "One", E3D_WINDOW_MODE_NOTCREATED);
	mainwindow->setModeBorderless();
	//mainwindow->setPosition(100, 100); //useless in fullscreen
	mainwindow->show();

	//TODO when writing the Threading class, make sure to run this BEFORE creating the next window
	thread w1(ThreadLoop, mainwindow);

	Window* secondwindow = new Window(window_width, window_height, "Two");
	secondwindow->show();
	secondwindow->setPosition(100, 100);
	
	thread w2(ThreadLoop, secondwindow);

	Window thirdwindow(window_width, window_height, "Three");
	thirdwindow.show();
	thirdwindow.setPosition(300, 300);

	thread w3(ThirdLoop, thirdwindow);
	//ThirdLoop(thirdwindow);

	while (running)
	{
		glfwWaitEvents(); //necessary because some events must process on the main thread
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
#ifdef _DEBUG
#pragma comment(linker, "/subsystem:console") //display a debug console to show warnings and errors, etc.
#endif
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