#pragma once
#include "Camera.h"
#include "SystemUtils.h"
#include "memtrace.h"

class ParallaxBackground
{
private:
	SystemUtils::Texture m_layer1;
	SystemUtils::Texture m_layer2;
	SystemUtils::Texture m_layer3;
	SystemUtils::Texture m_layer4;
	SystemUtils::Texture m_bgGradient;
	void m_drawLayer(const SystemUtils::Texture& texture, const Camera& camera, float speedMultiplier);

public:
	ParallaxBackground(const char* bggradient, const char* layer1, const char* layer2, const char* layer3, const char* layer4)
		: m_layer1(layer1)
		, m_layer2(layer2)
		, m_layer3(layer3)
		, m_layer4(layer4)
		, m_bgGradient(bggradient)
	{ }
	void draw(const Camera& camera);
};
