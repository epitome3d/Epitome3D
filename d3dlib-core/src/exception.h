#pragma once

#include <Windows.h>

namespace D3DLIB
{
	enum ErrorLevel
	{
		OK = 0,
		Info = 1,
		Warning = 2,
		Error = 3,
		Critical = 4
	};

	void DisplayMessage(HWND window, ErrorLevel level, bool debugonly, bool ignoreverbosity, LPCWSTR string, LPCWSTR title);
	void KillAll(bool debugonly, UINT exitcode);

	//*** GLOBALS ***//

	///<summary>The minimum level of message shown.  If set to zero, no messages will be displayed (not recommended).  If set to Critical, only critical messages will be displayed.  Otherwise, only messages of the selected level and above will be displayed.</summary>
	extern ErrorLevel _verbosity;
}