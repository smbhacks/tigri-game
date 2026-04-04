#include "Player.h"
#include "Platform.h"
#include "Game.h"
#include "GameUtils.h"

void Player::m_tickCollChecks()
{
	const float normalBounceSpeed = 12.0f;
	const float dashedBounceSpeed = 14.0f;
	for (auto& platform : m_platformsRef)
	{
		bool collided = m_collBox.checkCollision(platform->getCollBox());
		if (collided)
		{
			m_ySpeed = m_dashingDownwards ? -dashedBounceSpeed : -normalBounceSpeed;
			m_dashingDownwards = false;
			m_y = platform->getY() - m_collBox.getBox().height; // not perfect but good 'nuff
			break;
		}
	}
}

void Player::m_handleControlling()
{
	const Controller& controller = Game::getController();
	const float sideAcceleration = 0.8f;
	const float friction = 0.5f;
	const float downwardsDashSpeed = 30.0f;

	if (controller.isPressingRight())
	{
		m_xAcceleration = sideAcceleration;
	}
	else if (controller.isPressingLeft())
	{
		m_xAcceleration = -sideAcceleration;
	}
	else
	{
		m_xAcceleration = GameUtils::sign(m_xSpeed) * friction * -1;
		m_xAcceleration = GameUtils::clamp(m_xAcceleration, -1 * abs(m_xSpeed), abs(m_xSpeed));
	}

	if (controller.isPressingDown() && !m_dashingDownwards)
	{
		m_ySpeed = downwardsDashSpeed;
		m_dashingDownwards = true;
	}
}

void Player::m_handlePhysics()
{
	const float maxSideSpeed = 6.5f;
	m_xSpeed = GameUtils::clamp(m_xSpeed, -maxSideSpeed, maxSideSpeed);
	m_yAcceleration = 0.2f;
	m_applyPhysics();
}

void Player::tick()
{
	m_handleControlling();
	m_handlePhysics();
	m_tickCollChecks();
}
