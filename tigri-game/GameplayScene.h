#pragma once
#include <vector>
#include <memory>
#include "Scene.h"
#include "Entity.h"
#include "Player.h"
#include "Debuggable.h"
#include "Platform.h"
#include "TickTimer.h"
#include "ParallaxBackground.h"

class GameplayScene : public Scene, private Debuggable
{
private:
	Player m_player;
	Camera m_camera;
	TickTimer m_platformBaseSpeedIncreaseTimer;
	float m_platformBaseSpeed;
	TickTimer m_platformSpawnTimer;
	std::vector<std::unique_ptr<Platform>> m_platforms;
	SystemUtils::Music m_bgMusic;
	SystemUtils::Font m_scoreFont;
	TickTimer m_scoreTimer;
	size_t m_score;
	float m_getRandomPlatformSpeed();
	void m_drawScore();
	ParallaxBackground m_bg;

public:
	GameplayScene();
	void tick() override;
	void draw() override;
};
