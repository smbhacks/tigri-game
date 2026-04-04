#pragma once
#include "SDL.h"
#include "SDLW.h"
#include "Debuggable.h"
#include "Scene.h"
#include "Controller.h"

class Game : private Debuggable
{
private:
	SDLW_Renderer& m_renderer;
	bool m_isRunning = true;
	Scene* m_scene = new Scene();
	static Controller m_controller;

public:
	Game(SDLW_Renderer& renderer) 
		: Debuggable("Game")
		, m_renderer(renderer)
	{}
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