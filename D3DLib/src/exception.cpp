#include "exception.h"

namespace D3DLIB
{
	ErrorLevel _verbosity = Error;

	void DisplayMessage(HWND window, ErrorLevel level, bool debugonly, bool ignoreverbosity, LPCWSTR string, LPCWSTR title)
	{
		if (debugonly)
		{
			#ifdef _DEBUG

			UINT icon = MB_ICONINFORMATION;

			if (level == ErrorLevel::Critical || level == ErrorLevel::Error) { icon = MB_ICONERROR; }
			if (level == ErrorLevel::Warning) { icon = MB_ICONEXCLAMATION; }

			if ((ignoreverbosity) || (level >= _verbosity && _verbosity != 0)) { MessageBox(window, string, title, MB_OK | icon); };

			#endif
		}
		else
		{
			UINT icon = MB_ICONINFORMATION;

			if (level == ErrorLevel::Critical || level == ErrorLevel::Error) { icon = MB_ICONERROR; }
			if (level == ErrorLevel::Warning) { icon = MB_ICONEXCLAMATION; }

			if ((ignoreverbosity) || (level >= _verbosity && _verbosity != 0)) { MessageBox(window, string, title, MB_OK | icon); };
		}
	}

	void KillAll(bool debugonly, UINT exitcode)
	{
		if (debugonly)
		{
			#ifdef _DEBUG
			ExitProcess(exitcode);
			#endif
		}
		else
		{
			ExitProcess(exitcode);
		}
	}
}