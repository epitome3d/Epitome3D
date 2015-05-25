#pragma once

#include <GL/freeglut.h>

namespace EPITOME
{
	static void Initialize(int argc, char** argv);

	#ifdef WINDOWS
		#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
		#include <shellapi.h> //Windows API requirement
		/*
		Convenient wrapper for Initialize(argc, argv) for Windows.  Can return argc and argv for use.
		*/
		inline static void Initialize(int& argc, char**& argv)
		{
			LPWSTR *szArglist;
			szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
			argv = (char**)szArglist;
			Initialize(argc, (char**)szArglist);
		}
		/*
		Convenient wrapper for Initialize(argc, argv) for Windows.
		*/
		inline static void Initialize()
		{
			Initialize(0, 0);
		}
	#endif
}