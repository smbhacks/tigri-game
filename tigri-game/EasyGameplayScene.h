#pragma once
#include "GameplayScene.h"
#include "memtrace.h"

/// <summary>
/// Könnyű (Easy) nehézségi szintű játékmenetet megvalósító jelenet osztály.
/// </summary>
class EasyGameplayScene : public GameplayScene
{
private:
	ParallaxBackground m_bg;
	SystemUtils::Music m_bgMusic;

	/// <summary>Létrehoz és elhelyez új platformokat a pályán a könnyű mód szabályai szerint.</summary>
	void m_spawnPlatforms() override;

	/// <summary>Kiszámolja a platformok aktuális mozgási sebességét.</summary>
	/// <returns>A platform horizontális sebessége.</returns>
	float m_getRandomPlatformSpeed() override;

public:
	/// <summary>
	/// Konstruktor a könnyű pálya háttérképeinek és zenéinek betöltéséhez.
	/// </summary>
	EasyGameplayScene()
		: GameplayScene("src/easy/player.png")
		, m_bg("src/easy/bggradient.png", "src/easy/hillsfar.png", "src/easy/cloudsfar.png", "src/easy/hillsclose.png", "src/easy/cloudsclose.png")
		, m_bgMusic("src/easy/be_higher.mp3")
	{
		m_bgMusic.playMusic(-1);
	}

	/// <summary>Kirajzolja a jelenet összes elemét (háttér, platformok, játékos...).</summary>
	void draw() override;
};