#include "Game.h"
#include "SDL.h"

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;

	default:
		break;
	}
}

void Game::tick()
{
}

void Game::render()
{
	SDL_RenderClear(m_renderer.getRawPtr());
	SDL_RenderPresent(m_renderer.getRawPtr());
}
