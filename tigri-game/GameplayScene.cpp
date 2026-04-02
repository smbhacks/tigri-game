#include "GameplayScene.h"

void GameplayScene::tick()
{
	m_player.tick();
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
}

void GameplayScene::draw(const SDLW_Renderer& renderer)
{
	m_player.drawCollBox(renderer, m_camera);
	for (auto& platform : m_platforms)
	{
       platform->drawCollBox(renderer, m_camera);
	}
}