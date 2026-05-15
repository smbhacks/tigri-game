#pragma once
#include <cstdint>
#include "Controller.h"

// The core uses these so we can seperate the SDL and test builds easily

class SystemUtils
{
private:
	static inline bool shutdownRequestedFlag = false;

public:
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
		Music(const char* path);
		~Music();
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
	static void playMusic(const Music& music, int loops);
};