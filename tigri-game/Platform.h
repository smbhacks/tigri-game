#pragma once
#include "Entity.h"
#include "Camera.h"
#include "SystemUtils.h"

class Player;

class Platform : public Entity
{
protected:
	SystemUtils::Texture m_texture;

public:
	Platform(float xSpeed, float ySpeed, float xPos, float yPos)
		: Entity(Box(0, 0, 100, 8))
		, m_texture("src/platforms.png")
	{ 
		m_xSpeed = xSpeed;
		m_ySpeed = ySpeed;
		m_x = xPos;
		m_y = yPos;
	}
	virtual ~Platform() = default;
	virtual bool canBounce(const Player& player) = 0;
};