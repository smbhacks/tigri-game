#pragma once
#include "GameplayScene.h"

class EasyGameplayScene : public GameplayScene
{
private:
	ParallaxBackground m_bg;
	SystemUtils::Music m_bgMusic;

public:
	EasyGameplayScene()
		: GameplayScene("src/easy/player.png")
		, m_bg("src/easy/bggradient.png", "src/easy/hillsfar.png", "src/easy/cloudsfar.png", "src/easy/hillsclose.png", "src/easy/cloudsclose.png")
		, m_bgMusic("src/easy/be_higher.mp3")
	{
		m_bgMusic.playMusic(-1);
	}
	void draw() override;
};

