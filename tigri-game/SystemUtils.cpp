#include "SystemUtils.h"
#include "SDLW.h"
#include "SDL.h"

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
