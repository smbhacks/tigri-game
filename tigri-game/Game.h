#pragma once
#include "Debuggable.h"
#include "Scene.h"
#include "Controller.h"
#include "ParallaxBackground.h"
#include "GameplayScene.h"
#include "MenuScene.h"
#include "MiscEnums.h"
#include "EasyGameplayScene.h"
#include "memtrace.h"

/// <summary>
/// A játék fő vezérlőosztálya, amely kezeli a jeleneteket (scene) és a fő játékciklust.
/// </summary>
class Game : private Debuggable
{
public:
	/// <summary>
	/// A játék lehetséges fő állapotai.
	/// </summary>
	enum State
	{
		Menu,
		Gameplay
	};

private:
	Scene* m_scene = new Scene();
	static Controller m_controller;
	Game::State m_gameState;
	Gamemode m_gameMode;

public:
	/// <summary>
	/// Konstruktor, amely inicializálja a játékot a megadott kezdőállapottal.
	/// </summary>
	/// <param name="startingState">A játék indulási állapota (pl. Menu vagy Gameplay).</param>
	Game(State startingState)
		: Debuggable("Game")
		, m_gameState(startingState)
		, m_gameMode(Gamemode::Easy)
	{
		switch (m_gameState)
		{
		case Menu:
			changeScene(new MenuScene(m_gameMode), m_gameState);
			break;
		case Gameplay:
			changeScene(new EasyGameplayScene(), m_gameState);
			break;
		}
	}

	/// <summary>
	/// Destruktor, felszabadítja az aktuális jelenetet.
	/// </summary>
	~Game()
	{
		delete m_scene;
	}

	/// <summary>
	/// Képkockánként lefutó frissítési logika, amely továbbítja a hívást az aktuális jelenetnek, és kezeli a jelenetváltásokat.
	/// </summary>
	void tick();

	/// <summary>
	/// A teljes játékképernyő kirajzolása.
	/// </summary>
	void render();

	/// <summary>
	/// Lecseréli az aktuális jelenetet egy újra, és frissíti a játék állapotát.
	/// </summary>
	/// <param name="newScene">A memóriában lefoglalt új jelenet mutatója.</param>
	/// <param name="state">A játék új állapota.</param>
	void changeScene(Scene* newScene, Game::State state);

	/// <summary>
	/// Visszaadja a globális kontroller referenciáját.
	/// </summary>
	/// <returns>A kontroller referenciája.</returns>
	static Controller& getController() { return m_controller; };
};