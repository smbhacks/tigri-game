#pragma once
#include "GameplayScene.h"

class MediumGameplayScene : public GameplayScene
{
private:
	ParallaxBackground m_bg;
	SystemUtils::Music m_bgMusic;
	void m_spawnPlatforms() override;
	float m_getRandomPlatformSpeed() override;

public:
	MediumGameplayScene()
		: GameplayScene("src/hard/player.png")
		, m_bg("src/hard/bggradient.png", "src/hard/mountainsfar.png", "src/hard/cloudsfar.png", "src/hard/groundclose.png", "src/hard/cloudsclose.png")
		, m_bgMusic("src/hard/i_know_what_you_did_last_stage.mp3")
	{
		m_bgMusic.playMusic(-1);
	}
	void draw() override;
};

