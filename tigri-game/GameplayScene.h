#pragma once
#include <vector>
#include <memory>
#include "Scene.h"
#include "Entity.h"
#include "Player.h"
#include "Debuggable.h"
#include "Platform.h"
#include "TickTimer.h"

class GameplayScene : public Scene, private Debuggable
{
private:
	Player m_player;
	Camera m_camera;
	float m_getRandomPlatformSpeed();
	TickTimer m_platformBaseSpeedIncreaseTimer;
	float m_platformBaseSpeed;
	TickTimer m_platformSpawnTimer;
    std::vector<std::unique_ptr<Platform>> m_platforms;
	SystemUtils::Music m_bgMusic;

public:
	GameplayScene();
	void tick() override;
	void draw() override;
};

