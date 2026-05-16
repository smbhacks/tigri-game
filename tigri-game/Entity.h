#pragma once
#include "Collision.h"
#include "Debuggable.h"
#include "Scene.h"
#include "Camera.h"

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
	Entity(Box collBox, float x, float y)
		: m_x(x)
		, m_y(y)
		, m_collBox(m_x, m_y, collBox)
	{ }
	virtual ~Entity() = default;
	virtual void tick() = 0;
	void drawCollBox(const Camera& camera);
	virtual void draw(const Camera& camera) = 0;
	float howOffscreenX(const Camera& camera);
	CollisionBox& getCollBox() { return m_collBox; }
	float getY() const { return m_y; }
};