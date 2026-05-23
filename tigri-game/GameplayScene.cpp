#include "GameplayScene.h"
#include "memtrace.h"
#include "GameUtils.h"

GameplayScene::GameplayScene()
	: Scene()
	, Debuggable("GameplayScene")
	, m_platformSpawnTimer(120)
	, m_platformBaseSpeedIncreaseTimer(1)
	, m_platformBaseSpeed(-0.8f)
	, m_bgMusic("src/be_higher.mp3")
	, m_player(200.0f, -70.0f, Box(-75, -30, 150, 73), m_platforms)
{
	m_platforms.push_back(std::make_unique<Platform>(-0.6f, -0.2f, 200.0f, GameUtils::getRandomNum(500.0f, 650.0f)));
	m_platforms.push_back(std::make_unique<Platform>(-1.3f, -0.1f, 700.0f, GameUtils::getRandomNum(400.0f, 650.0f)));
	SystemUtils::playMusic(m_bgMusic, -1);
}

float GameplayScene::m_getRandomPlatformSpeed()
{
	static const float minBaseSpeed = -12.0f; // harder difficulty: -40.0f
	static const float randomnessIntervalSize = 2.0f;
	TickTimer& timer = m_platformBaseSpeedIncreaseTimer; // alias for this long ahh name
	if (m_platformBaseSpeed > minBaseSpeed && timer.state())
	{
		m_platformBaseSpeed -= 0.4f;
		GameUtils::clamp(m_platformBaseSpeed, minBaseSpeed, std::numeric_limits<float>::max());
		size_t newRestartVal = timer.getRestartVal() + 120;
		timer.setRestartVal(newRestartVal);
		timer.restart();
	}
	return GameUtils::getRandomNum(m_platformBaseSpeed, m_platformBaseSpeed - randomnessIntervalSize);
}

void GameplayScene::tick()
{
	m_camera.setX(m_camera.getX() + 0.2f);
	for (auto it = m_platforms.begin(); it != m_platforms.end();)
	{
		auto& platformPtr = *it;

		platformPtr->tick();
		if (platformPtr->howOffscreenX(m_camera) < -200.0f)
		{
			it = m_platforms.erase(it);
		}
		else
		{
			it++;
		}
	}
	m_platformBaseSpeedIncreaseTimer.tick();
	if (m_platformSpawnTimer.tick())
	{
		float xSpeed = m_getRandomPlatformSpeed();
		float ySpeed = GameUtils::getRandomNum(-0.5f, 0.5f);
		m_platforms.push_back(std::make_unique<Platform>(xSpeed, ySpeed, m_camera.getX()+1280.0f, GameUtils::getRandomNum(400.0f, 650.0f)));
		size_t maxTimeToWait = size_t(700.0f / abs(xSpeed));
		m_platformSpawnTimer.setRestartVal(GameUtils::getRandomNum<size_t>(10, maxTimeToWait));
		m_platformSpawnTimer.restart();
	}
	m_player.tick();
}

void GameplayScene::draw()
{
	m_player.draw(m_camera);
	m_player.drawCollBox(m_camera);
	for (auto& platform : m_platforms)
	{
       platform->drawCollBox(m_camera);
	}
}