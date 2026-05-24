#include "EasyGameplayScene.h"

void EasyGameplayScene::draw()
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