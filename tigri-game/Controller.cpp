#include "Controller.h"
#include "memtrace.h"

void Controller::handleInput(Key key, bool pressedState)
{
	switch (key)
	{
	case Key::Left:
		m_pressedLeftLastTick = m_pressingLeft;
		m_pressingLeft = pressedState;
		break;
	case Key::Right:
		m_pressedRightLastTick = m_pressingRight;
		m_pressingRight = pressedState;
		break;
	case Key::Down:
		m_pressedDownLastTick = m_pressingDown;
		m_pressingDown = pressedState;
		break;
	case Key::Up:
		m_pressedUpLastTick = m_pressingUp;
		m_pressingUp = pressedState;
		break;
	case Key::Confirm:
		m_pressedConfirmLastTick = m_pressingConfirm;
		m_pressingConfirm = pressedState;
		break;
	}
}
