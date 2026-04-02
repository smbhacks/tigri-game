#pragma once
#include <iostream>

class Debuggable
{
private:
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
	}
	Debuggable(const Debuggable& debuggable) :m_name(debuggable.m_name)
	{
		m_printCalled("Copy constructor");
	}
	~Debuggable()
	{
		m_printCalled("Destructor");
	}
};