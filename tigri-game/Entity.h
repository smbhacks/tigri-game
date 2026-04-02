#pragma once
#include "Collision.h"
#include "Debuggable.h"

class Entity : private Debuggable
{
private:
	float m_x = 0;
	float m_y = 0;
	float m_xSpeed = 0;
	float m_ySpeed = 0;
	float m_xAcceleration = 0;
	float m_yAcceleration = 0;
	CollisionBox m_collBox;

public:
	Entity(Box collBox) 
		: Debuggable("Entity")
		, m_collBox(m_x, m_y, collBox)
	{ }
	void move();
};