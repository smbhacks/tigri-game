#pragma once
#include "Scene.h"
#include "Entity.h"
#include "Debuggable.h"
#include "SDL.h"
#include "SDLW.h"

class GameplayScene : public Scene, private Debuggable
{
private:
	Entity m_player;
	Camera m_camera;

public:
	GameplayScene() 
		: Debuggable("GameplayScene")
		, Scene()
		, m_player(Box(0, 0, 200, 100))
	{ }
	void tick() override;
	void draw(const SDLW_Renderer& renderer) override;
};

