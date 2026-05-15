#pragma once
#include "Debuggable.h"

enum Key
{
	Right,
	Left,
	Down,
	Up
};

class Controller : private Debuggable
{
private:
	bool m_pressingRight = false;
	bool m_pressingLeft = false;
	bool m_pressingDown = false;
	bool m_pressingUp = false;

public:
	Controller()
		: Debuggable("Controller")
	{
	}
	void handleInput(Key key, bool pressedState);
	bool isPressingRight() const { return m_pressingRight; };
	bool isPressingLeft() const { return m_pressingLeft; };
	bool isPressingDown() const { return m_pressingDown; };
	bool isPressingUp() const { return m_pressingUp; };
};