#include "Controller.h"
#include "SDL.h"

static const SDL_Keycode leftKey  = SDLK_LEFT;
static const SDL_Keycode rightKey = SDLK_RIGHT;
static const SDL_Keycode downKey  = SDLK_DOWN;

void Controller::handleInput(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		bool isKeyDownEvent = (event.type == SDL_KEYDOWN);
		
		switch (event.key.keysym.sym)
		{
		case leftKey:
			m_pressingLeft = isKeyDownEvent;
			break;
		case rightKey:
			m_pressingRight = isKeyDownEvent;
			break;
		case downKey:
			m_pressingDown = isKeyDownEvent;
			break;
		}
	}
}
