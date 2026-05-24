#pragma once
#include "Defines.h"
#ifndef TEST_BUILD

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

/// <summary>
/// SDL_Renderer wrapper osztály.
/// </summary>
class SDLW_Renderer : private Debuggable
{
private:
	SDL_Renderer* m_renderer;
public:
	/// <summary>
	/// Alapértelmezett konstruktor, nullpéterrel inicializál.
	/// </summary>
	SDLW_Renderer()
		: Debuggable("SDLW_Renderer")
		, m_renderer(nullptr)
	{ }

	/// <summary>
	/// Konstruktor, amely létrehozza az SDL renderelőt a megadott ablakhoz.
	/// </summary>
	SDLW_Renderer(SDL_Window* window, int index, Uint32 flags)
		: Debuggable("SDLW_Renderer")
		, m_renderer(SDL_CreateRenderer(window, index, flags))
	{ }

	/// <summary>
	/// Áthelyező értékadás operátor az erőforrások átvételéhez.
	/// </summary>
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

	/// <summary>
	/// Destruktor, felszabadítja az SDL renderelőt.
	/// </summary>
	~SDLW_Renderer() { SDL_DestroyRenderer(m_renderer); }

	/// <summary>
	/// Visszaadja a mögöttes nyers SDL_Renderer mutatót.
	/// </summary>
	SDL_Renderer* getRawPtr() const { return m_renderer; }
};

/// <summary>
/// SDL_Window wrapper osztály.
/// </summary>
class SDLW_Window : private Debuggable
{
private:
	SDL_Window* m_window;
public:
	/// <summary>
	/// Konstruktor, létrehoz egy SDL ablakot a megadott paraméterekkel.
	/// </summary>
	SDLW_Window(const char* title, int x, int y, int w, int h, Uint32 flags)
		: Debuggable("SDLW_Window")
		, m_window(SDL_CreateWindow(title, x, y, w, h, flags))
	{ }

	/// <summary>
	/// Destruktor, bezárja és megsemmisíti az SDL ablakot.
	/// </summary>
	~SDLW_Window() { SDL_DestroyWindow(m_window); }

	/// <summary>
	/// Visszaadja a mögöttes nyers SDL_Window mutatót.
	/// </summary>
	SDL_Window* getRawPtr() const { return m_window; }
};

/// <summary>
/// Egy betöltött textúra példányát és annak referenciaszámlálóját tároló osztály.
/// </summary>
class TextureInstance : private Debuggable
{
public:
	const char* path;
	int counter = 1;
	SDL_Texture* texturePtr = nullptr;

	/// <summary>
	/// Konstruktor egy textúra példány létrehozásához elérési út alapján.
	/// </summary>
	explicit TextureInstance(const char* path)
		: Debuggable("TextureInstance")
		, path(path)
	{ }

	/// <summary>
	/// Összehasonlító operátor az elérési utak egyezőségének vizsgálatára.
	/// </summary>
	bool operator==(const TextureInstance& other) const
	{
		return strcmp(this->path, other.path) == 0;
	}
};

/// <summary>
/// Intelligens textúrakezelő osztály, amely megosztja az azonos fájlból betöltött textúrákat.
/// </summary>
class SDLW_Texture : private Debuggable
{
private:
	static SDL_Renderer* m_renderer;
	const char* m_path;
	SDL_Texture* m_texture;
	static std::vector<TextureInstance> m_textureInstances;

public:
	/// <summary>
	/// Konstruktor, betölti a textúrát a megadott útvonalról, vagy növeli a referenciát, ha már létezik.
	/// </summary>
	SDLW_Texture(const char* path);

	/// <summary>
	/// Destruktor, csökkenti a referenciaszámlálót, és törli a textúrát, ha elfogytak a hivatkozások.
	/// </summary>
	~SDLW_Texture();

	/// <summary>
	/// Beállítja a statikus renderelőt, amit a textúrák létrehozásához használ az osztály.
	/// </summary>
	static void setRenderer(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
	}

	/// <summary>
	/// Visszaadja az aktuálisan beállított statikus renderelőt.
	/// </summary>
	static SDL_Renderer* getRenderer()
	{
		return m_renderer;
	}

	/// <summary>
	/// Visszaadja a mögöttes nyers SDL_Texture mutatót.
	/// </summary>
	SDL_Texture* getRawPtr() const { return m_texture; }
};

/// <summary>
/// Mix_Music (háttérzene) wrapper osztály.
/// </summary>
class SDLW_Music : private Debuggable
{
private:
	Mix_Music* m_music;
public:
	/// <summary>
	/// Konstruktor, betölti a zenefájlt a megadott útvonalról.
	/// </summary>
	SDLW_Music(const char* path)
		: Debuggable("SDLW_Music")
		, m_music(Mix_LoadMUS(path))
	{ }

	/// <summary>
	/// Destruktor, felszabadítja a betöltött zenefájlt.
	/// </summary>
	~SDLW_Music()
	{
		Mix_FreeMusic(m_music);
	}

	/// <summary>
	/// Visszaadja a mögöttes nyers Mix_Music mutatót.
	/// </summary>
	Mix_Music* getRawPtr() const { return m_music; }
};

/// <summary>
/// TTF_Font (betűtípus) wrapper osztály.
/// </summary>
class SDLW_Font : private Debuggable
{
private:
	TTF_Font* m_font;
public:
	/// <summary>
	/// Konstruktor, betölti a betűtípust a megadott méretben.
	/// </summary>
	SDLW_Font(const char* path, int size)
		: Debuggable("SDLW_Font")
		, m_font(TTF_OpenFont(path, size))
	{ }

	/// <summary>
	/// Destruktor a betűtípus erőforrásainak kezeléséhez.
	/// </summary>
	~SDLW_Font()
	{
		// TTF_CloseFont(m_font);
	}

	/// <summary>
	/// Visszaadja a mögöttes nyers TTF_Font mutatót.
	/// </summary>
	TTF_Font* getRawPtr() const { return m_font; }
};

/// <summary>
/// SDL_Surface wrapper osztály.
/// </summary>
class SDLW_Surface : private Debuggable
{
private:
	SDL_Surface* m_surface;
public:
	/// <summary>
	/// Konstruktor, átveszi a tulajdonjogot egy létező SDL_Surface felett.
	/// </summary>
	SDLW_Surface(SDL_Surface* surface)
		: m_surface(surface)
	{ }

	/// <summary>
	/// Destruktor, felszabadítja az SDL felületet.
	/// </summary>
	~SDLW_Surface()
	{
		SDL_FreeSurface(m_surface);
	}

	/// <summary>
	/// Visszaadja a mögöttes nyers SDL_Surface mutatót.
	/// </summary>
	SDL_Surface* getRawPtr() const { return m_surface; }
};

#endif