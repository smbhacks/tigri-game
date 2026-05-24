#pragma once
#include "Camera.h"
#include "SystemUtils.h"

class ParallaxBackground
{
private:
	SystemUtils::Texture m_hillsFarTexture;
	SystemUtils::Texture m_hillsCloseTexture;
	SystemUtils::Texture m_cloudsFarTexture;
	SystemUtils::Texture m_cloudsCloseTexture;
	SystemUtils::Texture m_bgGradient;
	void m_drawLayer(const SystemUtils::Texture& texture, const Camera& camera, float speedMultiplier);

public:
	ParallaxBackground()
		: m_hillsFarTexture("src/hillsfar.png")
		, m_hillsCloseTexture("src/hillsclose.png")
		, m_cloudsFarTexture("src/cloudsfar.png")
		, m_cloudsCloseTexture("src/cloudsclose.png")
		, m_bgGradient("src/bggradient.png")
	{ }
	void draw(const Camera& camera);
};
