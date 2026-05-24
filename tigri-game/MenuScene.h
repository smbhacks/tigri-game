#pragma once
#include "Scene.h"
#include "SystemUtils.h"
#include "ParallaxBackground.h"
#include "memtrace.h"
#include "MiscEnums.h"

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
	MenuScene(Gamemode& modeRef);
	void tick() override;
	void draw() override;
};

