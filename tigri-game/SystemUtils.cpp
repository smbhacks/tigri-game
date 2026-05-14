#include "SystemUtils.h"
#include "Defines.h"
#include "memtrace.h"

#ifndef TEST_BUILD
#include "SDLW.h"
#include "SDL.h"
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
	: m_path(path)
{
	m_implementedInstance = new SDLW_Texture(path);
}

SystemUtils::Texture::~Texture()
{
	delete reinterpret_cast<SDLW_Texture*>(m_implementedInstance);
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
#endif

#ifdef TEST_BUILD
typedef char dummyType;

SystemUtils::Texture::Texture(const char* path)
	: m_path(path)
{
}

SystemUtils::Texture::~Texture()
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
#endif