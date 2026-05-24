#include "TickTimer.h"
#include "memtrace.h"

bool TickTimer::tick()
{
	if (m_ticksLeft == 0)
		return true;

	m_ticksLeft--;
	return state();
}

bool TickTimer::state()
{
	return m_ticksLeft == 0;
}

void TickTimer::restart()
{
	m_ticksLeft = m_ticksRestartVal;
}
