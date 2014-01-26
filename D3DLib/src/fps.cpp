#include "fps.h"

namespace D3DLIB
{

	FPS::FPS()
	{
	}

	FPS::FPS(const FPS& other)
	{
	}

	FPS::~FPS()
	{
	}

	void FPS::Initialize()
	{
		m_fps = 0;
		m_count = 0;
		m_startTime = timeGetTime();
		return;
	}

	void FPS::Frame()
	{
		m_count++;

		if(timeGetTime() >= (m_startTime + 1000))
		{
			m_fps = m_count;
			m_count = 0;
			m_startTime = timeGetTime();
		}
	}

	int FPS::GetFPS()
	{
		return m_fps;
	}

}