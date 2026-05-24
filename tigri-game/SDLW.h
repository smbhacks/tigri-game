#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Debuggable.h"
#include "GameUtils.h"
#include "memtrace.h"

class SDLW_Renderer : private Debuggable
{
private:
    SDL_Renderer* m_renderer;
public:
	SDLW_Renderer()
		: Debuggable("SDLW_Renderer")
		, m_renderer(nullptr)
	{ }
    SDLW_Renderer(SDL_Window* window, int index, Uint32 flags)
		: Debuggable("SDLW_Renderer")
		, m_renderer(SDL_CreateRenderer(window, index, flags))
	{}	
	SDLW_Renderer& operator=(SDLW_Renderer&& other) noexcept
	{
		if (this != &other)
		{
			if (m_renderer)
			{
				SDL_DestroyRenderer(m_renderer);
			}
			m_renderer = other.m_renderer;
			other.m_renderer = nullptr;
		}
		return *this;
	}	
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

class TextureInstance : private Debuggable
{
public:
	const char* path;
	int counter = 1;
	SDL_Texture* texturePtr = nullptr;
	explicit TextureInstance(const char* path) 
		: Debuggable("TextureInstance")
		, path(path)
	{}
    bool operator==(const TextureInstance& other) const
	{
		return strcmp(this->path, other.path) == 0;
	}
};

class SDLW_Texture : private Debuggable
{
private:
	static SDL_Renderer* m_renderer;
	const char* m_path;
	SDL_Texture* m_texture;
	static std::vector<TextureInstance> m_textureInstances;

public:
	SDLW_Texture(const char* path);
	~SDLW_Texture();
	static void setRenderer(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
	}
	static SDL_Renderer* getRenderer()
	{
		return m_renderer;
	}
	SDL_Texture* getRawPtr() const { return m_texture; }
};

class SDLW_Music : private Debuggable
{
private:
	Mix_Music* m_music;
public:
	SDLW_Music(const char* path)
		: Debuggable("SDLW_Music")
		, m_music(Mix_LoadMUS(path))
	{ }
	~SDLW_Music()
	{
		Mix_FreeMusic(m_music);
	}
	Mix_Music* getRawPtr() const { return m_music; }
};

class SDLW_Font : private Debuggable
{
private:
	TTF_Font* m_font;
public:
	SDLW_Font(const char* path, int size)
		: Debuggable("SDLW_Font")
		, m_font(TTF_OpenFont(path, size))
	{ }
	~SDLW_Font()
	{
//		TTF_CloseFont(m_font); // Todo: figure out why this throws
	}
	TTF_Font* getRawPtr() const { return m_font; }
};

class SDLW_Surface : private Debuggable
{
private:
	SDL_Surface* m_surface;
public:
	SDLW_Surface(SDL_Surface* surface)
		: m_surface(surface)
	{ }
	~SDLW_Surface()
	{
		SDL_FreeSurface(m_surface);
	}
	SDL_Surface* getRawPtr() const { return m_surface; }
};