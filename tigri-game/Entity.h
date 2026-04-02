#pragma once
#include "Collision.h"
#include "Debuggable.h"
#include "SDL.h"
#include "SDLW.h"
#include "Scene.h"

class Entity
{
protected:
	float m_x = 0;
	float m_y = 0;
	float m_xSpeed = 0;
	float m_ySpeed = 0;
	float m_xAcceleration = 0;
	float m_yAcceleration = 0;
	CollisionBox m_collBox;
	void m_applyPhysics();

public:
	Entity(Box collBox) 
		: m_collBox(m_x, m_y, collBox)
	{ }
	virtual ~Entity() = default;
	virtual void tick() = 0;
	void drawCollBox(const SDLW_Renderer& renderer, const Camera& camera);
	float howOffscreenX();
};