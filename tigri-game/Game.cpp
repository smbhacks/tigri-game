#include "Game.h"
#include "SystemUtils.h"
#include "memtrace.h"

Controller Game::m_controller;

void Game::tick()
{
	m_scene->tick();
	if (m_scene->isSceneReadyToShutdown())
	{
		switch (m_gamestate)
		{
		case Menu:
			changeScene(new GameplayScene(), State::Gameplay);
			break;
		case Gameplay:
			changeScene(new GameplayScene(), State::Gameplay);
			break;
		}
	}
}

void Game::render()
{
	SystemUtils::setRenderDrawColor(220, 220, 255, 255);
	SystemUtils::renderClear();
	m_scene->draw();
	SystemUtils::renderPresent();
}

void Game::changeScene(Scene* newScene, State state)
{
	delete m_scene;
	m_scene = newScene;
	m_gamestate = state;
}
