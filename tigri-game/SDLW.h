#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include "SDL.h"
#include "SDL_image.h"
#include "Debuggable.h"
#include "GameUtils.h"

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
	SDLW_Renderer(const SDLW_Renderer&) = delete;
	SDLW_Renderer& operator=(const SDLW_Renderer&) = delete;
	SDLW_Renderer(SDLW_Renderer&& other) noexcept
		: Debuggable("SDLW_Renderer")
		, m_renderer(other.m_renderer)
	{
		other.m_renderer = nullptr;
	}
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
	SDLW_Texture(const SDLW_Texture&) = delete;
	SDLW_Texture& operator=(const SDLW_Texture&) = delete;
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