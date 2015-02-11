#ifndef D3DLIB_FPS
#define D3DLIB_FPS

//linking
#pragma comment(lib, "winmm.lib")

//includes
#include <Windows.h>
#include <mmsystem.h>

namespace D3DLIB
{

	class FPS
	{
	public:
		FPS();

		void Initialize();
		void Frame(bool focused);
		int GetFPS();

	private:
		int m_fps, m_count;
		unsigned long m_startTime;
	};

}

#endif