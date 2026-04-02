#include "Entity.h"
#include "SDL.h"
#include "SDLW.h"
#include "Box.h"

void Entity::move()
{
	xSpeed += xAcceleration;
	ySpeed += yAcceleration;
	x += xSpeed;
	y += ySpeed;
}

void Entity::drawCollBox(const SDLW_Renderer& renderer, const Camera& camera)
{
	Box& box = m_collBox.getBox();
	SDL_FRect fRect = {
		.x = x + box.xOffs - camera.x,
		.y = y + box.yOffs - camera.y,
		.w = box.width,
		.h = box.height
	};
	SDL_SetRenderDrawColor(renderer.getRawPtr(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRectF(renderer.getRawPtr(), &fRect);
}
