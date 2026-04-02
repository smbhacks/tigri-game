#pragma once
#include "SDL.h"
#include "SDLW.h"
#include "Debuggable.h"
#include "Scene.h"

class Game : private Debuggable
{
private:
	SDLW_Renderer& m_renderer;
	bool m_isRunning = true;
	Scene* m_scene = new Scene();

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
	bool isRunning() { return m_isRunning; }
};

