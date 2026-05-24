#pragma once
#include "GameplayScene.h"
#include "memtrace.h"

/// <summary>
/// Nehéz nehézségi szintű játékmenetet megvalósító jelenet osztály.
/// </summary>
class HardGameplayScene : public GameplayScene
{
private:
	ParallaxBackground m_bg;
	SystemUtils::Music m_bgMusic;

	/// <summary>Létrehoz és elhelyez új platformokat a pályán a nehezebb mód szabályai szerint.</summary>
	void m_spawnPlatforms() override;

	/// <summary>Kiszámolja a platformok aktuális mozgási sebességét.</summary>
	/// <returns>A platform horizontális sebessége.</returns>
	float m_getRandomPlatformSpeed() override;

public:
	/// <summary>
	/// Konstruktor a nehezebb mód háttérképeinek és zenéinek betöltéséhez.
	/// </summary>
	HardGameplayScene()
		: GameplayScene("src/hard/player.png")
		, m_bg("src/hard/bggradient.png", "src/hard/mountainsfar.png", "src/hard/cloudsfar.png", "src/hard/groundclose.png", "src/hard/cloudsclose.png")
		, m_bgMusic("src/hard/i_know_what_you_did_last_stage.mp3")
	{
		m_bgMusic.playMusic(-1);
	}

	/// <summary>Kirajzolja a jelenet összes elemét (háttér, platformok, játékos...).</summary>
	void draw() override;
};