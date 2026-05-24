#pragma once
#include "Debuggable.h"
#include "memtrace.h"

/// <summary>
/// Képkocka (tick) alapú időzítő osztály.
/// </summary>
class TickTimer : private Debuggable
{
private:
	size_t m_ticksRestartVal;
	size_t m_ticksLeft;
public:
	/// <summary>
	/// Konstruktor az időzítő inicializálásához.
	/// </summary>
	/// <param name="ticks">Az időzítő alapértelmezett újraindulási értéke (tickekben).</param>
	TickTimer(size_t ticks = 0)
		: Debuggable("TickTimer")
		, m_ticksRestartVal(ticks)
		, m_ticksLeft(0)
	{
	}

	/// <summary>
	/// Lépteti az időzítőt egy képkockával (tick-kel).
	/// </summary>
	/// <returns>Igaz, ha az időzítő lejárt (0-ra ért), különben hamis.</returns>
	bool tick();

	/// <summary>
	/// Lekérdezi, hogy az időzítő lejárt-e.
	/// </summary>
	/// <returns>Igaz, ha az időzítő lejárt, különben hamis.</returns>
	bool state();

	/// <summary>
	/// Újraindítja az időzítőt a beállított kezdőértékkel.
	/// </summary>
	void restart();

	/// <summary>
	/// Beállítja az időzítő újraindulási értékét.
	/// </summary>
	/// <param name="ticks">Az új újraindulási érték (tickekben).</param>
	void setRestartVal(size_t ticks) { m_ticksRestartVal = ticks; }

	/// <summary>
	/// Visszaadja az időzítő újraindulási értékét.
	/// </summary>
	/// <returns>Az újraindulási érték (tickekben).</returns>
	size_t getRestartVal() const { return m_ticksRestartVal; }

	/// <summary>
	/// Visszaadja a hátralévő tickek számát.
	/// </summary>
	/// <returns>A hátralévő idő (tickekben).</returns>
	size_t getTicksLeft() const { return m_ticksLeft; }
};