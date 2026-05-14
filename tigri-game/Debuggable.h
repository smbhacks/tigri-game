#pragma once
#include <iostream>
#include "Defines.h"

class Debuggable
{
private:
	inline static int m_counter = 0;
	const char* m_name;
	void m_printCalled(const char* whatCalled)
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		std::cout << whatCalled << " called: " << m_name << " (" << this << ")\n";
#endif
	}

public:
	Debuggable() :m_name("?")
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		std::cout << "Debuggable::Debuggable() -> This shouldn't happen.\n";
#endif
	}
	Debuggable(const char* name) :m_name(name)
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		m_printCalled("Constructor");
#endif
		m_counter++;
	}
	Debuggable(const Debuggable& debuggable) :m_name(debuggable.m_name)
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		m_printCalled("Copy constructor");
#endif
		m_counter++;
	}
	virtual ~Debuggable()
	{
#ifdef PRINT_DEBUGGABLE_MESSAGES
		m_printCalled("Destructor");
#endif
		m_counter--;
	}
	static int getCounter() { return m_counter; }
};