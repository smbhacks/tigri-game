#include "GameplayScene.h"

void GameplayScene::tick()
{
	m_player.yAcceleration = 0.3;
	m_player.move();
}

void GameplayScene::draw(const SDLW_Renderer& renderer)
{
	m_player.drawCollBox(renderer, m_camera);
}