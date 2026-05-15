#pragma once
#include <vector>
#include <memory>
#include "Scene.h"
#include "Entity.h"
#include "Player.h"
#include "Debuggable.h"
#include "Platform.h"

class GameplayScene : public Scene, private Debuggable
{
private:
	Player m_player;
	Camera m_camera;
    std::vector<std::unique_ptr<Platform>> m_platforms;
	SystemUtils::Music m_bgMusic;

public:
	GameplayScene();
	void tick() override;
	void draw() override;
};

