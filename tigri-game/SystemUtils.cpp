#include "SystemUtils.h"
#include "Defines.h"
#include "memtrace.h"

#ifndef TEST_BUILD
#include "SDLW.h"
#include <SDL.h>
#endif

#ifndef TEST_BUILD
SDLW_Renderer renderer;

template<typename R, typename T>
R getSDLRect(const SystemUtils::Rect<T>& rect)
{
	return R{
		.x = rect.x,
		.y = rect.y,
		.w = rect.w,
		.h = rect.h
	};
}

SystemUtils::Texture::Texture(const char* path)
	: Resource(path)
{
	m_implementedInstance = new SDLW_Texture(path);
}
SystemUtils::Texture::~Texture()
{
	delete reinterpret_cast<SDLW_Texture*>(m_implementedInstance);
}
SystemUtils::Music::Music(const char* path)
	: Resource(path)
{
	m_implementedInstance = new SDLW_Music(path);
}
SystemUtils::Music::~Music()
{
	delete reinterpret_cast<SDLW_Music*>(m_implementedInstance);
}
SystemUtils::Font::Font(const char* path, int size)
	: Resource(path)
{
	m_implementedInstance = new SDLW_Font(path, size);
}
SystemUtils::Font::~Font()
{
	delete reinterpret_cast<SDLW_Font*>(m_implementedInstance);
}
SystemUtils::Text::Text(const Font& font, const char* string, const Color& color)
	: Resource("")
{
	SDLW_Font* sdlFont = reinterpret_cast<SDLW_Font*>(font.getInstance());
	SDLW_Surface textSurface(TTF_RenderText_Blended(sdlFont->getRawPtr(), string, SDL_Color(color.r, color.g, color.b, color.a)));
	m_textWidth = textSurface.getRawPtr()->w;
	m_textHeight = textSurface.getRawPtr()->h;
	m_implementedInstance = SDL_CreateTextureFromSurface(renderer.getRawPtr(), textSurface.getRawPtr());
}
SystemUtils::Text::~Text()
{
	SDL_DestroyTexture(reinterpret_cast<SDL_Texture*>(m_implementedInstance));
}
void SystemUtils::Text::render(const Rect<int>& dstRect)
{
	SDL_Rect sdlDstRect = getSDLRect<SDL_Rect>(dstRect);
	sdlDstRect.w = m_textWidth;
	sdlDstRect.h = m_textHeight;
	SDL_Rect srcRect = {
		.x = 0,
		.y = 0,
		.w = m_textWidth,
		.h = m_textHeight
	};
	SDL_RenderCopy(renderer.getRawPtr(), reinterpret_cast<SDL_Texture*>(m_implementedInstance), &srcRect, &sdlDstRect);
}

void SystemUtils::setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(renderer.getRawPtr(), r, g, b, a);
}

void SystemUtils::renderDrawRectF(const Rect<float>& rect)
{
	SDL_FRect sdlRect = getSDLRect<SDL_FRect>(rect);
	SDL_RenderDrawRectF(renderer.getRawPtr(), &sdlRect);
}

void SystemUtils::renderFillRectF(const Rect<float>& rect)
{
	SDL_FRect sdlRect = getSDLRect<SDL_FRect>(rect);
	SDL_RenderFillRectF(renderer.getRawPtr(), &sdlRect);
}

void SystemUtils::renderCopy(const Texture& texture, Rect<int>& srcRect, Rect<int>& dstRect)
{
	SDL_Rect sdlSrcRect = getSDLRect<SDL_Rect>(srcRect);
	SDL_Rect sdlDstRect = getSDLRect<SDL_Rect>(dstRect);
	SDL_Texture* finalPtr = reinterpret_cast<SDLW_Texture*>(texture.getInstance())->getRawPtr();
	SDL_RenderCopy(renderer.getRawPtr(), finalPtr, &sdlSrcRect, &sdlDstRect);
}

void SystemUtils::renderClear()
{
	SDL_RenderClear(renderer.getRawPtr());
}

void SystemUtils::renderPresent()
{
	SDL_RenderPresent(renderer.getRawPtr());
}

static void handleInput(const SDL_Event& event, Controller& controller)
{
	const SDL_Keycode leftKey = SDLK_LEFT;
	const SDL_Keycode rightKey = SDLK_RIGHT;
	const SDL_Keycode downKey = SDLK_DOWN;
	const SDL_KeyCode upKey = SDLK_UP;
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		bool isKeyDownEvent = (event.type == SDL_KEYDOWN);
		switch (event.key.keysym.sym)
		{
		case leftKey:
			controller.handleInput(Key::Left, isKeyDownEvent);
			break;
		case rightKey:
			controller.handleInput(Key::Right, isKeyDownEvent);
			break;
		case downKey:
			controller.handleInput(Key::Down, isKeyDownEvent);
			break;
		case upKey:
			controller.handleInput(Key::Up, isKeyDownEvent);
			break;
		}
	}
}

void SystemUtils::handleEvents(Controller& controller)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		handleInput(event, controller);
		switch (event.type)
		{
		case SDL_QUIT:
			shutdownRequestedFlag = true;
			break;

		default:
			break;
		}
	}
}

void SystemUtils::playMusic(const Music& music, int loops)
{
	Mix_Music* musicPtr = reinterpret_cast<SDLW_Music*>(music.getInstance())->getRawPtr();
	Mix_PlayMusic(musicPtr, loops);
}

#endif

#ifdef TEST_BUILD
typedef char dummyType;

SystemUtils::Texture::Texture(const char* path)
	: Resource(path)
{
}
SystemUtils::Texture::~Texture()
{
}

SystemUtils::Music::Music(const char* path)
	: Resource(path)
{
}

SystemUtils::Text::Text(const char* string)
	: Resource("")
{
}

SystemUtils::Text::~Text()
{
}

SystemUtils::Font::Font(const char* path)
	: Resource(path)
{
}

SystemUtils::Font::~Font()
{
}

SystemUtils::Music::~Music()
{
}

void SystemUtils::setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
}

void SystemUtils::renderDrawRectF(const Rect<float>& rect)
{
}

void SystemUtils::renderFillRectF(const Rect<float>& rect)
{
}

void SystemUtils::renderCopy(const Texture& texture, Rect<int>& srcRect, Rect<int>& dstRect)
{
}

void SystemUtils::renderClear()
{
}

void SystemUtils::renderPresent()
{
}

void SystemUtils::handleEvents(Controller& controller)
{
}

void SystemUtils::playMusic(const Music& music, int loops)
{
}

void SystemUtils::Text::render(const Rect<int>& dstRect)
{
}
#endif

