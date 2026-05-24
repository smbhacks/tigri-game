#include "ParallaxBackground.h"
#include "GameUtils.h"
#include "memtrace.h"

void ParallaxBackground::m_drawLayer(const SystemUtils::Texture& texture, const Camera& camera, float speedMultiplier)
{
	int startX = int(camera.getX() * speedMultiplier) % 3000;
	int widthNoWrap = 3000 - startX;
	widthNoWrap = GameUtils::clamp(widthNoWrap, 1, 1280);
	int widthAfterWrap = 1280 - widthNoWrap;
	SystemUtils::Rect<int> drawRegionNoWrap = {
		.x = startX,
		.y = 0,
		.w = widthNoWrap,
		.h = 720
	};
	SystemUtils::Rect<int> dstRegionNoWrap = {
		.x = 0,
		.y = 0,
		.w = widthNoWrap,
		.h = 720
	};
	SystemUtils::renderCopy(texture, drawRegionNoWrap, dstRegionNoWrap);
	if (widthAfterWrap > 0)
	{
		SystemUtils::Rect<int> drawRegionAfterWrap = {
			.x = 0,
			.y = 0,
			.w = widthAfterWrap,
			.h = 720
		};
		SystemUtils::Rect<int> dstRegionAfterWrap = {
			.x = widthNoWrap,
			.y = 0,
			.w = widthAfterWrap,
			.h = 720
		};
		SystemUtils::renderCopy(texture, drawRegionAfterWrap, dstRegionAfterWrap);
	}
}

void ParallaxBackground::draw(const Camera& camera)
{
	m_drawLayer(m_bgGradient, camera, 0.0f);
	m_drawLayer(m_cloudsFarTexture, camera, 1.0f);
	m_drawLayer(m_hillsFarTexture, camera, 0.5f);
	m_drawLayer(m_hillsCloseTexture, camera, 1.5f);
	m_drawLayer(m_cloudsCloseTexture, camera, 2.0f);
}
