#include "FragilePlatform.h"
#include "Player.h"
#include "memtrace.h"

void FragilePlatform::tick()
{
	m_applyPhysics();
}

void FragilePlatform::draw(const Camera& camera)
{
	SystemUtils::Rect<int> drawRegion = {
		.x = 100,
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

bool FragilePlatform::canBounce(const Player& player)
{
	return player.isDashingDownwards() == false;
}
