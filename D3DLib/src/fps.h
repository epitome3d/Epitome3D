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
		FPS(const FPS&);
		~FPS();

		void Initialize();
		void Frame();
		int GetFPS();

	private:
		int m_fps, m_count;
		unsigned long m_startTime;
	};

}

#endif