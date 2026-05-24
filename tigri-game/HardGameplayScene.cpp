#include "HardGameplayScene.h"
#include "GameUtils.h"
#include "FragilePlatform.h"
#include "SolidPlatform.h"
#include "memtrace.h"

void HardGameplayScene::draw()
{
	m_bg.draw(m_camera);
	for (auto& platform : m_platforms)
	{
		platform->draw(m_camera);
	}
	m_player.draw(m_camera);
	m_drawScore();
	if (m_gameOver)
	{
		m_drawGameOver();
	}
}

void HardGameplayScene::m_spawnPlatforms()
{
	m_platformBaseSpeedIncreaseTimer.tick();
	if (m_platformSpawnTimer.tick() && !m_gameOver)
	{
		float xSpeed = m_getRandomPlatformSpeed();
		float ySpeed = GameUtils::getRandomNum(-1.0f, 1.0f);
		float xPos = m_camera.getX() + 1280.0f;
		float yPos = GameUtils::getRandomNum(300.0f, 650.0f);
		float randomVal = GameUtils::getRandomNum(0.0f, 1.0f);
		if (randomVal < 0.5)
		{
			m_platforms.push_back(std::make_unique<FragilePlatform>(xSpeed, ySpeed, xPos, yPos));
		}
		else
		{
			m_platforms.push_back(std::make_unique<SolidPlatform>(xSpeed, ySpeed, xPos, yPos));
		}
		size_t maxTimeToWait = size_t(800.0f / abs(xSpeed));
		m_platformSpawnTimer.setRestartVal(GameUtils::getRandomNum<size_t>(10, maxTimeToWait));
		m_platformSpawnTimer.restart();
	}
}

float HardGameplayScene::m_getRandomPlatformSpeed()
{
	static const float minBaseSpeed = -40.0f;
	static const float randomnessIntervalSize = 5.0f;
	TickTimer& timer = m_platformBaseSpeedIncreaseTimer; // alias for this long ahh name
	if (m_platformBaseSpeed > minBaseSpeed && timer.state())
	{
		m_platformBaseSpeed -= 0.8f;
		GameUtils::clamp(m_platformBaseSpeed, minBaseSpeed, std::numeric_limits<float>::max());
		size_t newRestartVal = timer.getRestartVal() + 45;
		timer.setRestartVal(newRestartVal);
		timer.restart();
	}
	return GameUtils::getRandomNum(m_platformBaseSpeed - randomnessIntervalSize, m_platformBaseSpeed);
}