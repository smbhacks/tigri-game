#include "MenuScene.h"
#include "Game.h"

MenuScene::MenuScene()
	: Scene()
	, m_titleTexture("src/title.png")
	, m_music("src/gm04.mp3")
	, m_font("src/segoeuisl.ttf", 48)
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
	SystemUtils::renderTextWithShadow(m_font, "Press [ENTER] to start!", SystemUtils::Color(255, 255, 255, 255), instructionDstRegion, true);
}
