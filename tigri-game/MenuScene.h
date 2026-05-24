#pragma once
#include "Scene.h"
#include "SystemUtils.h"
#include "ParallaxBackground.h"
#include "MiscEnums.h"
#include "memtrace.h"

/// <summary>
/// A főmenüt reprezentáló jelenet osztály.
/// </summary>
class MenuScene : public Scene, private Debuggable
{
private:
	SystemUtils::Music m_music;
	SystemUtils::Texture m_titleTexture;
	ParallaxBackground m_bg;
	SystemUtils::Font m_font;
	SystemUtils::Font m_smallFont;
	Gamemode& modeRef;

public:
	/// <summary>
	/// Konstruktor, amely betölti a menü erőforrásait (zenék, textúrák, betűtípusok).
	/// </summary>
	/// <param name="modeRef">Referencia az aktuálisan kiválasztott játékmódra.</param>
	MenuScene(Gamemode& modeRef);

	/// <summary>
	/// Képkockánként lefutó logika, amely a felhasználói bemeneteket (menü navigáció, indítás) kezeli.
	/// </summary>
	void tick() override;

	/// <summary>
	/// Kirajzolja a menü vizuális elemeit, beleértve a hátteret.
	/// </summary>
	void draw() override;
};