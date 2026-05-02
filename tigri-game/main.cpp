#include <iostream>
#include "SDL.h"
#include "SDLW.h"
#include "Game.h"
#include "GameplayScene.h"
#include "Debuggable.h"

extern SDLW_Renderer renderer;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Couldn't init SDL2.\n";
		return -1;
	}
	SDLW_Window window("Tigri: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	renderer = SDLW_Renderer(window.getRawPtr(), -1, 0);
	SDLW_Texture::setRenderer(renderer.getRawPtr());
	
	Game game(renderer);
	game.changeScene(new GameplayScene());
	while (game.isRunning())
	{
		game.handleEvents();
		game.tick();
		game.render();
		SDL_Delay(16);
	}
	SDL_Quit();

	return 0;
}