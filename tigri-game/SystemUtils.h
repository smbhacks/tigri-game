#pragma once
#include <cstdint>

// The core uses these so we can seperate the SDL and test builds easily

namespace SystemUtils
{
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
	void setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void renderDrawRectF(const Rect<float>& rect);
	void renderFillRectF(const Rect<float>& rect);
	void renderCopy(const Texture& texture, Rect<int>& srcRect, Rect<int>& dstRect);
	void renderClear();
	void renderPresent();
};