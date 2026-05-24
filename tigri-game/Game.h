#pragma once
#include "Debuggable.h"
#include "Scene.h"
#include "Controller.h"
#include "ParallaxBackground.h"
#include "GameplayScene.h"
#include "MenuScene.h"
#include "memtrace.h"

class Game : private Debuggable
{
	enum State;
private:
	Scene* m_scene = new Scene();
	static Controller m_controller;
	State m_gamestate;

public:
	enum State
	{
		Menu,
		Gameplay
	};
	Game(State startingState)
		: Debuggable("Game")
		, m_gamestate(startingState)
	{
		switch (m_gamestate)
		{
		case Menu:
			changeScene(new MenuScene(), m_gamestate);
			break;
		case Gameplay:
			changeScene(new GameplayScene(), m_gamestate);
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
	void changeScene(Scene* newScene, State state);
	static Controller& getController() { return m_controller; }; // sorry this is probably stupid
};