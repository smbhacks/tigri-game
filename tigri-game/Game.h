#pragma once
#include "Debuggable.h"
#include "Scene.h"
#include "Controller.h"
#include "ParallaxBackground.h"
#include "GameplayScene.h"
#include "MenuScene.h"
#include "MiscEnums.h"
#include "memtrace.h"
#include "EasyGameplayScene.h"

class Game : private Debuggable
{
	enum State;
	enum Mode;
private:
	Scene* m_scene = new Scene();
	static Controller m_controller;
	Game::State m_gameState;
	Gamemode m_gameMode;

public:
	enum State
	{
		Menu,
		Gameplay
	};
	Game(State startingState)
		: Debuggable("Game")
		, m_gameState(startingState)
		, m_gameMode(Gamemode::Easy)
	{
		switch (m_gameState)
		{
		case Menu:
			changeScene(new MenuScene(m_gameMode), m_gameState);
			break;
		case Gameplay:
			changeScene(new EasyGameplayScene(), m_gameState);
			break;
		}
	}
	~Game()
	{
		delete m_scene;
	}
	//void handleEvents();
	void tick();
	void render();
	void changeScene(Scene* newScene, Game::State state);
	static Controller& getController() { return m_controller; }; // sorry this is probably stupid
};