#include "Entity.h"
#include "SDL.h"
#include "SDLW.h"
#include "Box.h"

void Entity::m_applyPhysics()
{
	m_xSpeed += m_xAcceleration;
	m_ySpeed += m_yAcceleration;
	m_x += m_xSpeed;
	m_y += m_ySpeed;
}

void Entity::drawCollBox(const SDLW_Renderer& renderer, const Camera& camera)
{
	Box& box = m_collBox.getBox();
	SDL_FRect hitboxRect = {
		.x = m_x + box.xOffs - camera.x,
		.y = m_y + box.yOffs - camera.y,
		.w = box.width,
		.h = box.height
	};
	SDL_SetRenderDrawColor(renderer.getRawPtr(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRectF(renderer.getRawPtr(), &hitboxRect);
	SDL_FRect hotpointRect = {
		.x = m_x - 3,
		.y = m_y - 3,
		.w = 7,
		.h = 7
	};
	SDL_SetRenderDrawColor(renderer.getRawPtr(), 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRectF(renderer.getRawPtr(), &hotpointRect);
}

float Entity::howOffscreenX()
{
	if (m_x < 0)
		return m_x;

	if (m_x >= 1280)
		return m_x - 1280 + 1;

	return 0;
}