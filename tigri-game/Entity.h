#pragma once
#include "Collision.h"
#include "Debuggable.h"
#include "SDL.h"
#include "SDLW.h"
#include "Scene.h"

class Entity : private Debuggable
{
private:
	CollisionBox m_collBox;

public:
	float x = 0;
	float y = 0;
	float xSpeed = 0;
	float ySpeed = 0;
	float xAcceleration = 0;
	float yAcceleration = 0;
	Entity(Box collBox) 
		: Debuggable("Entity")
		, m_collBox(x, y, collBox)
	{ }
	void move();
	void drawCollBox(const SDLW_Renderer& renderer, const Camera& camera);
};