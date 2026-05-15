#include <iostream>
#include "Defines.h"
#include "Game.h"
#include "GameplayScene.h"
#include "Debuggable.h"
#include "GameUtils.h"
#include "memtrace.h"

#ifdef TEST_BUILD
#include "gtest_lite.h"
#else
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDLW.h"
#endif

#ifndef TEST_BUILD
extern SDLW_Renderer renderer;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Couldn't init SDL2.\n";
		return -1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer error: " << Mix_GetError() << std::endl;
		return -1;
	}
	SDLW_Window window("Tigri: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	renderer = SDLW_Renderer(window.getRawPtr(), -1, 0);
	SDLW_Texture::setRenderer(renderer.getRawPtr());
	
	GameUtils::setRandomSeed(time(0));

	Game game;
	game.changeScene(new GameplayScene());
	while (!SystemUtils::isShutdownRequested())
	{
		SystemUtils::handleEvents(game.getController());
		game.tick();
		game.render();
		SDL_Delay(16);
	}
	SDL_Quit();

	return 0;
}
#endif

#ifdef TEST_BUILD
int main()
{
	struct TestEntity
	{
		float x, y;
		CollisionBox collBox;
		TestEntity(Box collBox, float x, float y)
			: x(x)
			, y(y)
			, collBox(this->x, this->y, collBox)
		{}
	};
	TestEntity t1(Box(0, 0, 10, 10), 0, 0);
	TestEntity t2(Box(0, 0, 10, 10), 10, 10);
	TEST(CollisionBox, checkCollision)
	{
		t1.x = 0;
		t1.y = 0;
		EXPECT_EQ(false, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 10;
		t1.y = 0;
		EXPECT_EQ(false, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 20;
		t1.y = 0;
		EXPECT_EQ(false, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 0;
		t1.y = 5;
		EXPECT_EQ(false, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 10;
		t1.y = 5;
		EXPECT_EQ(true, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 20;
		t1.y = 5;
		EXPECT_EQ(false, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 0;
		t1.y = 10;
		EXPECT_EQ(false, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 10;
		t1.y = 10;
		EXPECT_EQ(true, CollisionBox::checkCollision(t1.collBox, t2.collBox));
		t1.x = 20;
		t1.y = 10;
		EXPECT_EQ(false, CollisionBox::checkCollision(t1.collBox, t2.collBox));
	} END

	TEST(Game, Logic) {
		Game game;
		game.changeScene(new GameplayScene());
		for (int i = 0; i < 1000; i++)
		{
			EXPECT_NO_THROW(game.tick());
			EXPECT_NO_THROW(game.render());
		}
	} END

	TEST(GameUtils, clamp)
	{
		float lower = 10.0f;
		float upper = 20.0f;
		float average = (lower + upper) / 2;
		EXPECT_EQ(lower, GameUtils::clamp(lower - 1, lower, upper));
		EXPECT_EQ(upper, GameUtils::clamp(upper + 1, lower, upper));
		EXPECT_EQ(average, GameUtils::clamp(average, lower, upper));
	} END
}
#endif