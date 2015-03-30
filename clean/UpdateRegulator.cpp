#include "StdAfx.h"
#include "UpdateRegulator.h"

#include <mmsystem.h>


void AABSEngine::Utility::UpdateRegulator::SetUpdatesPerSecond(double updatesPerSecond)
{
	if(updatesPerSecond < 0.0) 
	{
		m_timeInterval = -1;
		m_nextUpdateTime = 0;

		return;
	}


	if(updatesPerSecond < 1E-10)
	{
		m_timeInterval = 0;
		m_nextUpdateTime = 0;
			
		return;
	}

	m_timeInterval = (DWORD)(1000.0 / updatesPerSecond); //updates per millisecond
	m_nextUpdateTime = timeGetTime() + m_timeInterval; 
}


bool AABSEngine::Utility::UpdateRegulator::IsReady()
{
	if(m_timeInterval == -1.0) return false;

	if(m_timeInterval == 0.0) return true;

	DWORD curTime = timeGetTime();

	if(curTime > m_nextUpdateTime)
	{
		double variator = 10.0;

		m_nextUpdateTime = curTime + m_timeInterval + ((2.0 * variator) * RandInterval() - variator); //(max - min) * t + min

		return true;
	}
	return false;
}


double AABSEngine::Utility::UpdateRegulator::RandInterval()const
{
	srand(rand() ^ time(NULL));
	return (double)rand() / RAND_MAX;
}