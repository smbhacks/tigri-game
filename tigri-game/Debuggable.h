#pragma once
#include <iostream>

class Debuggable
{
private:
	inline static int m_counter = 0;
	const char* m_name;
	void m_printCalled(const char* whatCalled)
	{
		std::cout << whatCalled << " called: " << m_name << " (" << this << ")\n";
	}

public:
	Debuggable() :m_name("?")
	{
		std::cout << "Debuggable::Debuggable() -> This shouldn't happen.\n";
	}
	Debuggable(const char* name) :m_name(name)
	{
		m_printCalled("Constructor");
		m_counter++;
	}
	Debuggable(const Debuggable& debuggable) :m_name(debuggable.m_name)
	{
		m_printCalled("Copy constructor");
		m_counter++;
	}
	virtual ~Debuggable()
	{
		m_printCalled("Destructor");
		m_counter--;
	}
	static int getCounter() { return m_counter; }
};