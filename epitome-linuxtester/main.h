#pragma once

#include <GL/freeglut.h>

void Init(int argc, char** argv);

static void RenderSceneCB();
static void InitializeGlutCallbacks();

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
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

#ifdef LINUX
int main(int argc, char** argv)
{
	FreeConsole();
	Init(argc, argv);
	glutMainLoop();

	return 0;
}
#endif