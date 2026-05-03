#pragma once
#include "Debuggable.h"
#include "Scene.h"
#include "Controller.h"

class Game : private Debuggable
{
private:
	bool m_isRunning = true;
	Scene* m_scene = new Scene();
	static Controller m_controller;

public:
	Game()
		: Debuggable("Game")
	{ }
	~Game()
	{
		delete m_scene;
	}
	void handleEvents();
	void tick();
	void render();
	void changeScene(Scene* newScene);
	bool isRunning() { return m_isRunning; }
	static const Controller& getController() { return m_controller; };
};