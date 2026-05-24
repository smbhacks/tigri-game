#include "SolidPlatform.h"
#include "Player.h"

void SolidPlatform::tick()
{
	m_applyPhysics();
}

void SolidPlatform::draw(const Camera& camera)
{
	SystemUtils::Rect<int> drawRegion = {
		.x = 0,
		.y = 0,
		.w = 100,
		.h = 32
	};
	SystemUtils::Rect<int> dest = {
		.x = (int)m_x - (int)camera.getX(),
		.y = (int)m_y - (int)camera.getY(),
		.w = 100,
		.h = 32
	};
	SystemUtils::renderCopy(m_texture, drawRegion, dest);
}
