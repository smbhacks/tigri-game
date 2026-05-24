#pragma once
#include <cstdint>
#include "Controller.h"
#include "memtrace.h"

// The core uses these so we can seperate the SDL and test builds easily

class SystemUtils
{
private:
	static inline bool shutdownRequestedFlag = false;

public:
	template<typename T>
	struct Rect {
		T x;
		T y;
		T w;
		T h;
	};
	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
	class Resource
	{
	protected:
		const char* m_path;
		void* m_implementedInstance = nullptr;
	public:
		Resource(const char* path)
			: m_path(path)
		{ }
		void* getInstance() const { return m_implementedInstance; }
		const char* getPath() const { return m_path; }
	};
	class Texture : public Resource 
	{
	public:
		Texture(const char* path);
		~Texture();
	};
	class Music : public Resource 
	{
	public:
		void playMusic(int loops);
		Music(const char* path);
		~Music();
	};
	class Font : public Resource
	{
	public:
		Font(const char* path, int size);
		~Font();
	};
	class Text : public Resource
	{
	private:
		int m_textWidth;
		int m_textHeight;
	public:
		Text(const Font& font, const char* string, const Color& color);
		~Text();
		void render(const Rect<int>& dstRect, int xOffset = 0, int yOffset = 0);
		int getWidth() const { return m_textWidth; }
		int getHeight() const { return m_textHeight; }
	};
	static bool isShutdownRequested() { return shutdownRequestedFlag; }
	static void setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	static void renderDrawRectF(const Rect<float>& rect);
	static void renderFillRectF(const Rect<float>& rect);
	static void renderCopy(const Texture& texture, Rect<int>& srcRect, Rect<int>& dstRect);
	static void renderClear();
	static void renderPresent();
	static void handleEvents(Controller& controller);
	static void renderTextWithShadow(const Font& font, const char* string, const Color& color, Rect<int> dstRect, bool centerX = false);
};