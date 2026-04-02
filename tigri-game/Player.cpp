#include "Player.h"

void Player::tick()
{
	m_yAcceleration = 0.2f;
	m_applyPhysics();
}
