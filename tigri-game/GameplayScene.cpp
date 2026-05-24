#include "GameplayScene.h"
#include "GameUtils.h"
#include "SolidPlatform.h"
#include "FragilePlatform.h"
#include "Game.h"
#include "memtrace.h"

GameplayScene::GameplayScene()
	: Scene()
	, Debuggable("GameplayScene")
	, m_platformSpawnTimer(120)
	, m_platformBaseSpeedIncreaseTimer(1)
	, m_platformBaseSpeed(-0.8f)
	, m_bgMusic("src/be_higher.mp3")
	, m_youDiedMusic("src/you_died.mp3")
	, m_smallFont("src/segoeuisl.ttf", 48)
	, m_bigFont("src/segoeuisl.ttf", 130)
	, m_player(200.0f, -70.0f, Box(-75, -30, 150, 73), m_platforms)
	, m_scoreTimer(60)
	, m_score(0)
	, m_gameOver(false)
	, m_diedTextTimer(60*4)
	, m_diedOptionTimer(60*2)
{
	m_platforms.push_back(std::make_unique<SolidPlatform>(-0.6f, -0.2f, 200.0f, GameUtils::getRandomNum(500.0f, 650.0f)));
	m_platforms.push_back(std::make_unique<SolidPlatform>(-1.3f, -0.1f, 700.0f, GameUtils::getRandomNum(400.0f, 650.0f)));
	m_bgMusic.playMusic(-1);
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

void GameplayScene::m_tickGameOver()
{
	m_diedTextTimer.tick();
	if (m_diedTextTimer.state() == true)
	{
		m_diedOptionTimer.tick();
		Controller& controller = Game::getController();
		if (controller.isPressingConfirm())
		{
			m_shutdownSceneFlag = true;
		}
	}
}

void GameplayScene::m_spawnPlatforms()
{
	m_platformBaseSpeedIncreaseTimer.tick();
	if (m_platformSpawnTimer.tick() && !m_gameOver)
	{
		float xSpeed = m_getRandomPlatformSpeed();
		float ySpeed = GameUtils::getRandomNum(-0.5f, 0.5f);
		float xPos = m_camera.getX() + 1280.0f;
		float yPos = GameUtils::getRandomNum(400.0f, 650.0f);
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
	m_spawnPlatforms();
	m_player.tick();
	if (m_player.hasDied() && !m_gameOver)
	{
		m_gameOver = true;
		m_youDiedMusic.playMusic(0);
		m_diedTextTimer.restart();
		m_diedOptionTimer.restart();
	}
	if (m_gameOver)
	{
		m_tickGameOver();
	}
}

void GameplayScene::m_drawScore()
{
	const static int shadowOffset = 2;
	SystemUtils::Rect<int> scoreDstRect = {
		.x = 32 + shadowOffset,
		.y = 10 + shadowOffset
	};
	if (m_scoreTimer.tick() && !m_gameOver)
	{
		m_score++;
		m_scoreTimer.restart();
	}
	std::string scoreString = "Score: " + std::to_string(m_score);
	SystemUtils::renderTextWithShadow(m_smallFont, scoreString.c_str(), SystemUtils::Color(255, 255, 255, 255), scoreDstRect);
}

int getAlphaFromTickTimer(const TickTimer& timer)
{
	int alpha = 255.0f * (timer.getRestartVal() - timer.getTicksLeft()) / timer.getRestartVal();
	alpha = GameUtils::clamp(alpha, 1, 255);
	return alpha;
}

void GameplayScene::m_drawGameOver()
{
	SystemUtils::Rect<int> dstRect{
		.y = 250,
	};
	SystemUtils::Color redColor(100, 10, 10);
	redColor.a = getAlphaFromTickTimer(m_diedTextTimer);
	SystemUtils::renderTextWithShadow(m_bigFont, "YOU DIED", redColor, dstRect, true);
	if (m_diedTextTimer.state() == true)
	{
		dstRect.y += 150;
		redColor.a = getAlphaFromTickTimer(m_diedOptionTimer);
		SystemUtils::renderTextWithShadow(m_smallFont, "Press [ENTER]...", redColor, dstRect, true);
	}
}

void GameplayScene::draw()
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