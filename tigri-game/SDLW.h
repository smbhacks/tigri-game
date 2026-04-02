#pragma once
#include <iostream>
#include "SDL.h"
#include "Debuggable.h"

class SDLW_Renderer : private Debuggable
{
private:
    SDL_Renderer* m_renderer;
public:
    SDLW_Renderer(SDL_Window* window, int index, Uint32 flags)
		: Debuggable("SDLW_Renderer")
		, m_renderer(SDL_CreateRenderer(window, index, flags))
	{}
	~SDLW_Renderer() { SDL_DestroyRenderer(m_renderer); }

	SDL_Renderer* getRawPtr() const { return m_renderer; }
};

class SDLW_Window : private Debuggable
{
private:
	SDL_Window* m_window;
public:
    SDLW_Window(const char* title, int x, int y, int w, int h, Uint32 flags)
		: Debuggable("SDLW_Window")
		, m_window(SDL_CreateWindow(title, x, y, w, h, flags))
	{}
	~SDLW_Window() { SDL_DestroyWindow(m_window); }

	SDL_Window* getRawPtr() const { return m_window; }
};