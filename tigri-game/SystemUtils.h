#pragma once
#include <cstdint>
#include "Controller.h"

// The core uses these so we can seperate the SDL and test builds easily

class SystemUtils
{
private:
	static inline bool shutdownRequestedFlag = false;

public:
	class Texture
	{
	private:
		const char* m_path;
		void* m_implementedInstance = nullptr;
	public:
		Texture(const char* path);
		~Texture();
		void* getInstance() const { return m_implementedInstance; }
	};
	template<typename T>
	struct Rect {
		T x;
		T y;
		T w;
		T h;
	};
	static bool isShutdownRequested() { return shutdownRequestedFlag; }
	static void setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	static void renderDrawRectF(const Rect<float>& rect);
	static void renderFillRectF(const Rect<float>& rect);
	static void renderCopy(const Texture& texture, Rect<int>& srcRect, Rect<int>& dstRect);
	static void renderClear();
	static void renderPresent();
	static void handleEvents(Controller& controller);
};