#pragma once
#include <vector>
#include <memory>
#include "Scene.h"
#include "Entity.h"
#include "Player.h"
#include "Debuggable.h"
#include "Platform.h"
#include "TickTimer.h"
#include "ParallaxBackground.h"
#include "memtrace.h"

/// <summary>
/// A játékmenet alapvető logikáját (játékos, platformok, pontszám, game over) összefogó absztrakt jelenet osztály.
/// </summary>
class GameplayScene : public Scene, private Debuggable
{
protected:
	Player m_player;
	Camera m_camera;
	TickTimer m_platformBaseSpeedIncreaseTimer;
	float m_platformBaseSpeed;
	TickTimer m_platformSpawnTimer;
	std::vector<std::unique_ptr<Platform>> m_platforms;
	SystemUtils::Music m_youDiedMusic;
	SystemUtils::Font m_smallFont;
	SystemUtils::Font m_bigFont;
	TickTimer m_scoreTimer;
	size_t m_score;

	/// <summary>Visszaad egy véletlenszerű sebességet az új platformokhoz (leszármazottakban implementálandó).</summary>
	virtual float m_getRandomPlatformSpeed() = 0;

	/// <summary>Kirajzolja a játékos aktuális pontszámát vetett árnyékkal.</summary>
	void m_drawScore();
	bool m_gameOver;
	TickTimer m_diedTextTimer;

	/// <summary>A Game Over állapot logikájának frissítése (pl. kilépés gombnyomásra).</summary>
	void m_tickGameOver();

	/// <summary>Új platformok spawnolása a pályán (leszármazottakban implementálandó).</summary>
	virtual void m_spawnPlatforms() = 0;

	/// <summary>A Game Over feliratok és instrukciók kirajzolása fade-in hatással.</summary>
	void m_drawGameOver();
	TickTimer m_diedOptionTimer;

public:
	/// <summary>
	/// Konstruktor a játéktér és a megosztott erőforrások inicializálásához.
	/// </summary>
	/// <param name="playerPngPath">A játékos textúrájának elérési útja.</param>
	GameplayScene(const char* playerPngPath);

	/// <summary>Képkockánként lefutó logika: fizika, kamera, spawnolás és ütközésvizsgálat.</summary>
	void tick() override;

	/// <summary>A játéktér kirajzolása (leszármazottakban implementálandó).</summary>
	virtual void draw() = 0;
};