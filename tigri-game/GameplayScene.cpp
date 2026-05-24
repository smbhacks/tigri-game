#include "GameplayScene.h"
#include "memtrace.h"
#include "GameUtils.h"
#include "SolidPlatform.h"
#include "FragilePlatform.h"

GameplayScene::GameplayScene()
	: Scene()
	, Debuggable("GameplayScene")
	, m_platformSpawnTimer(120)
	, m_platformBaseSpeedIncreaseTimer(1)
	, m_platformBaseSpeed(-0.8f)
	, m_bgMusic("src/be_higher.mp3")
	, m_scoreFont("src/segoeuisl.ttf", 48)
	, m_player(200.0f, -70.0f, Box(-75, -30, 150, 73), m_platforms)
	, m_scoreTimer(60)
	, m_score(0)
{
	m_platforms.push_back(std::make_unique<SolidPlatform>(-0.6f, -0.2f, 200.0f, GameUtils::getRandomNum(500.0f, 650.0f)));
	m_platforms.push_back(std::make_unique<SolidPlatform>(-1.3f, -0.1f, 700.0f, GameUtils::getRandomNum(400.0f, 650.0f)));
	SystemUtils::playMusic(m_bgMusic, -1);
}

float GameplayScene::m_getRandomPlatformSpeed()
{
	static const float minBaseSpeed = -13.0f; // harder difficulty: -40.0f
	static const float randomnessIntervalSize = 2.0f;
	TickTimer& timer = m_platformBaseSpeedIncreaseTimer; // alias for this long ahh name
	if (m_platformBaseSpeed > minBaseSpeed && timer.state())
	{
		m_platformBaseSpeed -= 0.4f;
		GameUtils::clamp(m_platformBaseSpeed, minBaseSpeed, std::numeric_limits<float>::max());
		size_t newRestartVal = timer.getRestartVal() + 30;
		timer.setRestartVal(newRestartVal);
		timer.restart();
	}
	return GameUtils::getRandomNum(m_platformBaseSpeed - randomnessIntervalSize, m_platformBaseSpeed);
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
		float xPos = m_camera.getX() + 1280.0f;
		float yPos = GameUtils::getRandomNum(400.0f, 650.0f);
		std::unique_ptr<Platform> platformPtr;
		float randomVal = GameUtils::getRandomNum(0.0f, 1.0f);
		if (randomVal < 0.33)
		{
			m_platforms.push_back(std::make_unique<FragilePlatform>(xSpeed, ySpeed, xPos, yPos));
		}
		else
		{
			m_platforms.push_back(std::make_unique<SolidPlatform>(xSpeed, ySpeed, xPos, yPos));
		}
		size_t maxTimeToWait = size_t(700.0f / abs(xSpeed));
		m_platformSpawnTimer.setRestartVal(GameUtils::getRandomNum<size_t>(10, maxTimeToWait));
		m_platformSpawnTimer.restart();
	}
	m_player.tick();
}

void GameplayScene::m_drawScore()
{
	const static int shadowOffset = 2;
	SystemUtils::Rect<int> scoreDstRect = {
		.x = 32 + shadowOffset,
		.y = 10 + shadowOffset
	};
	if (m_scoreTimer.tick())
	{
		m_score++;
		m_scoreTimer.restart();
	}
	std::string scoreString = "Score: " + std::to_string(m_score);
	SystemUtils::Text(m_scoreFont, scoreString.c_str(), SystemUtils::Color(0, 0, 0, 128)).render(scoreDstRect);
	scoreDstRect.x -= shadowOffset;
	scoreDstRect.y -= shadowOffset;
	SystemUtils::Text(m_scoreFont, scoreString.c_str(), SystemUtils::Color(255, 255, 255, 255)).render(scoreDstRect);
}

void GameplayScene::draw()
{
	m_bg.draw(m_camera);
	for (auto& platform : m_platforms)
	{
		platform->draw(m_camera);
		platform->drawCollBox(m_camera);
	}
	m_player.draw(m_camera);
	m_player.drawCollBox(m_camera);
	m_drawScore();
}