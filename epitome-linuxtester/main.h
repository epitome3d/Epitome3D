#pragma once

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

#include <GL/freeglut.h>

void Init(int argc, char** argv);

static void RenderSceneCB();
static void InitializeGlutCallbacks();

#ifdef WIN32
#include <shellapi.h>
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
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
#ifdef UNIX
int main(int argc, char** argv)
{
	FreeConsole();
	Init(argc, argv);
	glutMainLoop();

	return 0;
}
#endif