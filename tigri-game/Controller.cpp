#include "Controller.h"

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
	}
}
