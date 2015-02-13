#ifndef EPITOME_TIMER
#define EPITOME_TIMER

//includes
#include <Windows.h>

namespace EPITOME
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