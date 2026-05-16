#include "GameplayScene.h"
#include "memtrace.h"
#include "GameUtils.h"

GameplayScene::GameplayScene()
	: Scene()
	, Debuggable("GameplayScene")
	, m_bgMusic("src/be_higher.mp3")
	, m_player(200.0f, -70.0f, Box(-75, -30, 150, 73), m_platforms)
{
	m_platforms.push_back(std::make_unique<Platform>(-0.6f, 0.0f, 200.0f, GameUtils::getRandomNum(500.0f, 650.0f)));
	m_platforms.push_back(std::make_unique<Platform>(-0.8f, 0.0f, 1000.0f, GameUtils::getRandomNum(400.0f, 650.0f)));
	SystemUtils::playMusic(m_bgMusic, -1);
}

void GameplayScene::tick()
{
	m_camera.setX(m_camera.getX() + 1.0f);
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