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
#include "memtrace.h"

class GameplayScene : public Scene, private Debuggable
{
protected:
	Player m_player;
	Camera m_camera;
	TickTimer m_platformBaseSpeedIncreaseTimer;
	float m_platformBaseSpeed;
	TickTimer m_platformSpawnTimer;
	std::vector<std::unique_ptr<Platform>> m_platforms;
	SystemUtils::Music m_youDiedMusic;
	SystemUtils::Font m_smallFont;
	SystemUtils::Font m_bigFont;
	TickTimer m_scoreTimer;
	size_t m_score;
	float m_getRandomPlatformSpeed();
	void m_drawScore();
	bool m_gameOver;
	TickTimer m_diedTextTimer;
	void m_tickGameOver();
	void m_spawnPlatforms();
	void m_drawGameOver();
	TickTimer m_diedOptionTimer;

public:
	GameplayScene(const char* playerPngPath);
	void tick() override;
	virtual void draw() = 0;
};
