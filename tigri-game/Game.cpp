#include "Game.h"
#include "SystemUtils.h"
#include "EasyGameplayScene.h"
#include "HardGameplayScene.h"
#include "memtrace.h"

Controller Game::m_controller;

void Game::tick()
{
	m_scene->tick();
	if (m_scene->isSceneReadyToShutdown())
	{
		switch (m_gameState)
		{
		case Game::State::Menu:
			switch (m_gameMode)
			{
			case Gamemode::Easy:
				changeScene(new EasyGameplayScene(), Game::State::Gameplay);
				break;
			case Gamemode::Hard:
				changeScene(new HardGameplayScene(), Game::State::Gameplay);
				break;
			default:
				break;
			}
			break;
		case Game::State::Gameplay:
			changeScene(new MenuScene(m_gameMode), Game::State::Menu);
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

void Game::changeScene(Scene* newScene, Game::State state)
{
	delete m_scene;
	m_scene = newScene;
	m_gameState = state;
}