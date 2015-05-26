#pragma once

#include <GL/freeglut.h>
#include "system.h"

namespace EPITOME
{
	//Initializes Epitome3D components.  Requires argc and argv to be present.
	static void Initialize(int argc, char** argv);

	//Destroys all Epitome3D components.  Should be called before exiting the app.
	static void Exit();

	#ifdef WINDOWS
		#include <shellapi.h> //Windows API requirement
		
		//Convenient wrapper for Initialize(argc, argv) for Windows.  Can return argc and argv for use.
		inline static void Initialize(int& argc, char**& argv)
		{
			LPWSTR *szArglist;
			szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
			argv = (char**)szArglist;
			Initialize(argc, (char**)szArglist);
		}

		//Convenient wrapper for Initialize(argc, argv) for Windows.
		inline static void Initialize()
		{
			Initialize(0, 0);
		}
	#endif
}