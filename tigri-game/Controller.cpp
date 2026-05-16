#include "Controller.h"
#include "memtrace.h"

void Controller::tick()
{
	m_pressedLeftLastTick = m_pressingLeft;
	m_pressedRightLastTick = m_pressingRight;
	m_pressedDownLastTick = m_pressingDown;
	m_pressedUpLastTick = m_pressingUp;
}

void Controller::handleInput(Key key, bool pressedState)
{
	switch (key)
	{
	case Key::Left:
		m_pressingLeft = pressedState;
		break;
	case Key::Right:
		m_pressingRight = pressedState;
		break;
	case Key::Down:
		m_pressingDown = pressedState;
		break;
	case Key::Up:
		m_pressingUp = pressedState;
		break;
	}
}
