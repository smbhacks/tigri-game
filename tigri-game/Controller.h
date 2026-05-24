#pragma once
#include "Debuggable.h"
#include "memtrace.h"

enum Key
{
	Right,
	Left,
	Down,
	Up,
	Confirm
};

class Controller : private Debuggable
{
private:
	bool m_pressingRight = false;
	bool m_pressingLeft = false;
	bool m_pressingDown = false;
	bool m_pressingUp = false;
	bool m_pressingConfirm = false;
	bool m_pressedRightLastTick = false;
	bool m_pressedLeftLastTick = false;
	bool m_pressedDownLastTick = false;
	bool m_pressedUpLastTick = false;
	bool m_pressedConfirmLastTick = false;

public:
	Controller()
		: Debuggable("Controller")
	{
	}
	void setPrevs();
	void handleInput(Key key, bool pressedState);
	bool isPressingRight() const { return m_pressingRight; };
	bool isPressingLeft() const { return m_pressingLeft; };
	bool isPressingDown() const { return m_pressingDown; };
	bool isPressingUp() const { return m_pressingUp; };
	bool isPressingConfirm() const { return m_pressingConfirm; }
	bool pressedRightLastTick() const { return m_pressedRightLastTick; }
	bool pressedLeftLastTick() const { return m_pressedLeftLastTick; }
	bool pressedDownLastTick() const { return m_pressedDownLastTick; }
	bool pressedUpLastTick() const { return m_pressedUpLastTick; }
	bool pressedConfirmLastTick() const { return m_pressedConfirmLastTick; }
};