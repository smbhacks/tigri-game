#pragma once
#include <iostream>
#include "SDL.h"
#include "Debuggable.h"

template<class T>
class SDLW_RefGetter
{
protected:
	T& m_reference;
public:
	SDLW_RefGetter(T& reference) : m_reference(reference) {}
	T* getRawPtr()
	{
		return &m_reference;
	}
};

class SDLW_Renderer : private Debuggable, public SDLW_RefGetter<SDL_Renderer>
{
private:
	SDL_Renderer* m_renderer;
public:
	SDLW_Renderer(SDL_Window* window, int index, Uint32 flags) 
		: Debuggable("SDLW_Renderer")
		, m_renderer(SDL_CreateRenderer(window, index, flags)) 
		, SDLW_RefGetter(*m_renderer)
	{}
	~SDLW_Renderer() { SDL_DestroyRenderer(m_renderer); }
};

class SDLW_Window : private Debuggable, public SDLW_RefGetter<SDL_Window>
{
private:
	SDL_Window* m_window;
public:
	SDLW_Window(const char* title, int x, int y, int w, int h, Uint32 flags)
		: Debuggable("SDLW_Window")
		, m_window(SDL_CreateWindow(title, x, y, w, h, flags))
		, SDLW_RefGetter(*m_window)
	{}
	~SDLW_Window() { SDL_DestroyWindow(m_window); }
};