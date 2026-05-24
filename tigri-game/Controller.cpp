#include "Controller.h"
#include "memtrace.h"

void Controller::setPrevs()
{
	m_pressedLeftLastTick = m_pressingLeft;
	m_pressedRightLastTick = m_pressingRight;
	m_pressedDownLastTick = m_pressingDown;
	m_pressedUpLastTick = m_pressingUp;
	m_pressedConfirmLastTick = m_pressingConfirm;
	m_pressedSelectLastTick = m_pressingSelect;
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
	case Key::Confirm:
		m_pressingConfirm = pressedState;
		break;
	case Key::Select:
		m_pressingSelect = pressedState;
		break;
	}
}
