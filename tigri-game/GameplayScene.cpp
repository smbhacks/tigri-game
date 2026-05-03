#include "GameplayScene.h"

void GameplayScene::tick()
{
	for (auto it = m_platforms.begin(); it != m_platforms.end();)
	{
		auto& platformPtr = *it;

		platformPtr->tick();
		if (platformPtr->howOffscreenX() < -200.0f)
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
	m_player.draw();
	m_player.drawCollBox(m_camera);
	for (auto& platform : m_platforms)
	{
       platform->drawCollBox(m_camera);
	}
}