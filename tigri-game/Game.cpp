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
	m_scene->tick();
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_renderer.getRawPtr(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer.getRawPtr());
	m_scene->draw(m_renderer);
	SDL_RenderPresent(m_renderer.getRawPtr());
}

void Game::changeScene(Scene* newScene)
{
	delete m_scene;
	m_scene = newScene;
}
