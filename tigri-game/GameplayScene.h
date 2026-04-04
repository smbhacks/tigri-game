#pragma once
#include <vector>
#include <memory>
#include "Scene.h"
#include "Entity.h"
#include "Player.h"
#include "Debuggable.h"
#include "SDL.h"
#include "SDLW.h"
#include "Platform.h"

class GameplayScene : public Scene, private Debuggable
{
private:
	Player m_player;
	Camera m_camera;
    std::vector<std::unique_ptr<Platform>> m_platforms;

public:
	GameplayScene() 
		: Debuggable("GameplayScene")
		, Scene()
		, m_player(Box(0, 0, 200, 100), m_platforms)
	{
        m_platforms.push_back(std::make_unique<Platform>(Box(0, 0, 100, 32)));
	}
	void tick() override;
	void draw(const SDLW_Renderer& renderer) override;
};

