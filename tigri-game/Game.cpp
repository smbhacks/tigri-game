#include "Game.h"
#include "SystemUtils.h"
#include "memtrace.h"

Controller Game::m_controller;

void Game::tick()
{
	m_controller.tick();
	m_scene->tick();
}

void Game::render()
{
	SystemUtils::setRenderDrawColor(220, 220, 255, 255);
	SystemUtils::renderClear();
	m_scene->draw();
	SystemUtils::renderPresent();
}

void Game::changeScene(Scene* newScene)
{
	delete m_scene;
	m_scene = newScene;
}
