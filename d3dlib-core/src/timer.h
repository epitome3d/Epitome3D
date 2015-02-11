#ifndef D3DLIB_TIMER
#define D3DLIB_TIMER

//includes
#include <Windows.h>

namespace D3DLIB
{

	class Timer
	{
	public:
		Timer();
		Timer(const Timer&);
		~Timer();

		bool Initialize();
		void Frame();
		float GetTime();

	private:
		INT64 m_frequency;
		float m_ticksPerMs;
		INT64 m_startTime;
		float m_frameTime;
	};

}

#endif