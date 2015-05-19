#ifndef EPITOME_CPU
#define EPITOME_CPU

//linking
#pragma comment(lib, "pdh.lib")

//includes
#include <Pdh.h>

namespace EPITOME
{

	class CPU
	{
	public:
		CPU();
		CPU(const CPU&);
		~CPU();

		void Initialize();
		void Shutdown();
		void Frame();
		int GetCPUPercentage();

	private:
		bool m_canReadCPU;
		HQUERY m_queryHandle;
		HCOUNTER m_counterHandle;
		unsigned long m_lastSampleTime;
		long m_CPUUsage;
	};

}

#endif