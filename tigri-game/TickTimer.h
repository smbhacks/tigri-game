#pragma once
#include "Debuggable.h"
#include "memtrace.h"

class TickTimer : private Debuggable
{
private:
	size_t m_ticksRestartVal;
	size_t m_ticksLeft;
public:
	TickTimer(size_t ticks = 0)
		: Debuggable("TickTimer")
		, m_ticksRestartVal(ticks)
		, m_ticksLeft(0)
	{ }
	bool tick();
	bool state();
	void restart();
	void setRestartVal(size_t ticks) { m_ticksRestartVal = ticks; }
	size_t getRestartVal() const { return m_ticksRestartVal; }
	size_t getTicksLeft() const { return m_ticksLeft; }
};
