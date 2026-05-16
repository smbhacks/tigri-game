#include "Entity.h"
#include "Box.h"
#include "SystemUtils.h"
#include "memtrace.h"

void Entity::m_applyPhysics()
{
	m_xSpeed += m_xAcceleration;
	m_ySpeed += m_yAcceleration;
	m_x += m_xSpeed;
	m_y += m_ySpeed;
}

void Entity::drawCollBox(const Camera& camera)
{
	Box& box = m_collBox.getBox();
	SystemUtils::Rect<float> hitboxRect = {
		.x = m_x + box.xOffs - camera.getX(),
		.y = m_y + box.yOffs - camera.getY(),
		.w = box.width,
		.h = box.height
	};
	SystemUtils::setRenderDrawColor(255, 0, 0, 255); //SDL_SetRenderDrawColor(renderer.getRawPtr(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SystemUtils::renderDrawRectF(hitboxRect); //SDL_RenderDrawRectF(renderer.getRawPtr(), &hitboxRect);
	SystemUtils::Rect<float> hotpointRect = {
		.x = m_x - 3 - camera.getX(),
		.y = m_y - 3 - camera.getY(),
		.w = 7,
		.h = 7
	};
	SystemUtils::setRenderDrawColor(0, 0, 255, 255); //SDL_SetRenderDrawColor(renderer.getRawPtr(), 0, 0, 255, SDL_ALPHA_OPAQUE);
	SystemUtils::renderFillRectF(hotpointRect); //SDL_RenderFillRectF(renderer.getRawPtr(), &hotpointRect);
}

float Entity::howOffscreenX(const Camera& camera)
{
	float relativePos = m_x - camera.getX();
	if (relativePos < 0)
		return relativePos;

	if (relativePos >= 1280)
		return relativePos - 1280 + 1;

	return 0;
}