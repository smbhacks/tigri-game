#include "Player.h"
#include "Platform.h"

void Player::m_tickPhysics()
{
	m_yAcceleration = 0.2f;
	m_applyPhysics();
}

void Player::m_tickCollChecks()
{
	for (auto& platform : m_platformsRef)
	{
		bool collided = m_collBox.checkCollision(platform->getCollBox());
		if (collided)
		{
			m_ySpeed = -13.0f;
			m_y = platform->getY() - m_collBox.getBox().height; // not perfect but good 'nuff
			break;
		}
	}
}

void Player::tick()
{
	m_tickPhysics();
	m_tickCollChecks();
}
