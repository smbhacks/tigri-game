#pragma once
#include <iostream>
#include "Defines.h"
#include "memtrace.h"

/// <summary>
/// Hibakeresést segítő ősosztály, amely számolja a példányokat és opcionálisan logolja az életciklusukat.
/// </summary>
class Debuggable
{
private:
	inline static int m_counter = 0;
	const char* m_name;

	/// <summary>
	/// Segédfüggvény a hívások (például konstruktor/destruktor) konzolra írásához.
	/// </summary>
	/// <param name="whatCalled">A hívó esemény vagy függvény neve.</param>
	void m_printCalled(const char* whatCalled)
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		std::cout << whatCalled << " called: " << m_name << " (" << this << ")\n";
#endif
	}

public:
	/// <summary>
	/// Alapértelmezett konstruktor (használata nem ajánlott, ismeretlen névvel inicializál).
	/// </summary>
	Debuggable() :m_name("?")
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		std::cout << "Debuggable::Debuggable() -> This shouldn't happen.\n";
#endif
	}

	/// <summary>
	/// Paraméteres konstruktor, beállítja az objektum nevét és növeli a számlálót.
	/// </summary>
	/// <param name="name">Az objektum azonosító neve a logoláshoz.</param>
	Debuggable(const char* name) :m_name(name)
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		m_printCalled("Constructor");
#endif
		m_counter++;
	}

	/// <summary>
	/// Másoló konstruktor, átmásolja a nevet és növeli a számlálót.
	/// </summary>
	/// <param name="debuggable">A másolandó objektum.</param>
	Debuggable(const Debuggable& debuggable) :m_name(debuggable.m_name)
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		m_printCalled("Copy constructor");
#endif
		m_counter++;
	}

	/// <summary>
	/// Virtuális destruktor, csökkenti a példányszámlálót és logolja a törlést.
	/// </summary>
	virtual ~Debuggable()
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		m_printCalled("Destructor");
#endif
		m_counter--;
	}

	/// <summary>
	/// Visszaadja az aktuálisan memóriában lévő Debuggable objektumok számát.
	/// </summary>
	/// <returns>A példányok száma.</returns>
	static int getCounter() { return m_counter; }
};