#include "Game.h"
#include "SystemUtils.h"

Controller Game::m_controller;

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_controller.handleInput(event);
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;

		default:
			break;
		}
	}
}

void Game::tick()
{
	m_scene->tick();
}

void Game::render()
{
	SystemUtils::setRenderDrawColor(255, 255, 255, 255);
	SystemUtils::renderClear();
	m_scene->draw();
	SystemUtils::renderPresent();
}

void Game::changeScene(Scene* newScene)
{
	delete m_scene;
	m_scene = newScene;
}
