#include "MenuScene.h"
#include "Game.h"
#include "memtrace.h"

MenuScene::MenuScene(Gamemode& modeRef)
	: Scene()
	, modeRef(modeRef)
	, m_titleTexture("src/title.png")
	, m_music("src/gm04.mp3")
	, m_font("src/segoeuisl.ttf", 48)
	, m_smallFont("src/segoeuisl.ttf", 24)
	, m_bg("src/easy/bggradient.png", "src/easy/hillsfar.png", "src/easy/cloudsfar.png", "src/easy/hillsclose.png", "src/easy/cloudsclose.png")
{
	m_music.playMusic(-1);
}

void MenuScene::tick()
{
	Controller& controller = Game::getController();
	if (controller.isPressingConfirm() && !controller.pressedConfirmLastTick())
	{
		m_shutdownSceneFlag = true;
	}
	if (controller.isPressingSelect() && !controller.pressedSelectLastTick())
	{
		modeRef = Gamemode((int)modeRef + 1);
		if (modeRef >= Gamemode::_LastElement)
		{
			modeRef = Gamemode::_FirstElement;
		}
	}
}

void MenuScene::draw()
{
	m_bg.draw(Camera());
	SystemUtils::Rect<int> titleDrawRegion{
		.x = 0,
		.y = 0,
		.w = 655,
		.h = 324
	};
	SystemUtils::Rect<int> titleDstRegion{
		.x = (1280 - 655) / 2,
		.y = 100,
		.w = 655,
		.h = 324
	};
	SystemUtils::renderCopy(m_titleTexture, titleDrawRegion, titleDstRegion);
	SystemUtils::Rect<int> instructionDstRegion{
		.x = 0, // will be centered
		.y = 720 / 2 + 160,
		.w = 0,
		.h = 0
	};
	SystemUtils::Color whiteColor(255, 255, 255, 255);
	SystemUtils::renderTextWithShadow(m_font, "Press [ENTER] to start!", whiteColor, instructionDstRegion, true);
	instructionDstRegion.y += 64;
	std::string gamemodeText;
	switch (modeRef)
	{
	case Gamemode::Easy:
		gamemodeText = "Easy mode";
		break;
	case Gamemode::Medium:
		gamemodeText = "Medium mode";
		break;
	}
	SystemUtils::renderTextWithShadow(m_smallFont, ("Press [SPACE] to select: " + gamemodeText).c_str(), whiteColor, instructionDstRegion, true);
}
