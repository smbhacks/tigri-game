#pragma once
#include "Debuggable.h"
#include "SDL.h"

class Controller : private Debuggable
{
private:
	bool m_pressingRight = false;
	bool m_pressingLeft = false;
	bool m_pressingDown = false;

public:
	Controller()
		: Debuggable("Controller")
	{
	}
	void handleInput(SDL_Event& event);
	bool isPressingRight() const { return m_pressingRight; };
	bool isPressingLeft() const { return m_pressingLeft; };
	bool isPressingDown() const { return m_pressingDown; };
};