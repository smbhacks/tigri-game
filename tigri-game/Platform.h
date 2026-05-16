#pragma once
#include "Entity.h"
#include "Camera.h"

class Platform : public Entity, private Debuggable
{
public:
	Platform(float xSpeed, float ySpeed, float xPos, float yPos)
		: Entity(Box(0, 0, 100, 32))
		, Debuggable("Platform")
	{ 
		m_xSpeed = xSpeed;
		m_ySpeed = ySpeed;
		m_x = xPos;
		m_y = yPos;
	}
	void tick() override;
	void draw(const Camera& camera) override;
};