#include "cpu.h"

namespace EPITOME
{

	CPU::CPU()
	{
	}

	CPU::CPU(const CPU& other)
	{
	}

	CPU::~CPU()
	{
	}

	void CPU::Initialize()
	{
		PDH_STATUS status;

		//initialize the flag indicating whether the object can read the system CPU
		m_canReadCPU = true;

		//create a query object to poll CPU usage
		status = PdhOpenQuery(NULL, 0, &m_queryHandle);
		if (status != ERROR_SUCCESS)
		{
			m_canReadCPU = false;
		}

		//set the query object to poll all CPUs
		status = PdhAddCounter(m_queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_counterHandle);
		if (status != ERROR_SUCCESS)
		{
			m_canReadCPU = false;
		}

		m_lastSampleTime = GetTickCount();
		m_CPUUsage = 0;

		return;
	}

	void CPU::Shutdown()
	{
		if(m_canReadCPU)
		{
			PdhCloseQuery(m_queryHandle);
		}

		return;
	}

	void CPU::Frame()
	{
		PDH_FMT_COUNTERVALUE value;

		if (m_canReadCPU)
		{
			if ((m_lastSampleTime + 1000) < GetTickCount())
			{
				m_lastSampleTime = GetTickCount();
				PdhCollectQueryData(m_queryHandle);
				PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);
				m_CPUUsage = value.longValue;
			}
		}

		return;
	}

	int CPU::GetCPUPercentage()
	{
		int usage;
		if(m_canReadCPU)
		{
			usage = (int)m_CPUUsage;
		}
		else
		{
			usage = 0;
		}

		return usage;
	}

}