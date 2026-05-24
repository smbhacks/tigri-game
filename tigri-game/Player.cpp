#include "Player.h"
#include "Platform.h"
#include "Game.h"
#include "GameUtils.h"
#include "Camera.h"
#include "memtrace.h"

const static int dashAnimFrameTime = 4;
const static int fallingAnimFrameTime = 6;

void Player::m_tickCollChecks()
{
	const float normalBounceSpeed = 14.0f;
	const float dashedBounceSpeed = 16.0f;
	for (auto& platform : m_platformsRef)
	{
		bool collided = CollisionBox::checkCollision(m_collBox, platform->getCollBox());
		if (collided && platform->canBounce(*this))
		{
			m_ySpeed = m_dashingDownwards ? -dashedBounceSpeed : -normalBounceSpeed;
			m_dashingDownwards = false;
			m_dashCounterOngoing = false;
			m_dashCounter = 0;
			m_lowerGravityAllowed = true;
			m_y = platform->getY() - m_collBox.getBox().height - m_collBox.getBox().yOffs;
			break;
		}
	}
}

void Player::m_handleControlling()
{
	const Controller& controller = Game::getController();
	const float sideAcceleration = 0.8f;
	const float friction = 0.5f;

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
		m_dashCounterOngoing = true;
	}

	if (controller.isPressingUp() && m_lowerGravityAllowed)
	{
		m_gravity = 0.28f;
	}
	else
	{
		m_gravity = 0.48f;
		m_lowerGravityAllowed = false;
	}
}

void Player::m_handlePhysics()
{
	const float maxSideSpeed = 6.5f;
	m_xSpeed = GameUtils::clamp(m_xSpeed, -maxSideSpeed, maxSideSpeed);
	m_yAcceleration = m_gravity;
	m_applyPhysics();
	m_fallingStarted = m_ySpeed > 0;
	if (!m_fallingStarted)
	{
		m_fallingCounter = 0;
	}
	else
	{
		m_lowerGravityAllowed = false;
	}
}

void Player::m_handleDash()
{
	const float downwardsDashSpeed = 40.0f;
	if (m_dashCounterOngoing)
	{
		if (++m_dashCounter >= 3*dashAnimFrameTime)
		{
			m_ySpeed = downwardsDashSpeed;
			m_dashingDownwards = true;
			m_dashCounterOngoing = false;
		}
	}
}

void Player::tick()
{
	if (!m_died)
	{
		m_handleControlling();
		m_handleDash();
		m_handlePhysics();
		m_tickCollChecks();
		if (m_y > 900)
		{
			m_died = true;
		}
	}
}

void Player::m_drawDashing(SystemUtils::Rect<int>& drawRegion)
{
	const int dashAnimFramesX[] = {
		0,
		1 * 200,
		2 * 200,
		3 * 200
	};
	drawRegion.x = dashAnimFramesX[m_dashCounter / dashAnimFrameTime];
	drawRegion.y = 200;
}

void Player::m_drawDefault(SystemUtils::Rect<int>& drawRegion)
{
	if (m_fallingStarted && m_fallingCounter < 3 * fallingAnimFrameTime)
	{
		m_fallingCounter++;
	}
	drawRegion.x = (m_fallingCounter / fallingAnimFrameTime) * 200;
}

void Player::draw(const Camera& camera)
{
	SystemUtils::Rect<int> drawRegion = {
		.x = 0,
		.y = 0,
		.w = 200,
		.h = 200
	};
	if (m_dashCounterOngoing || m_dashingDownwards)
	{
		Player::m_drawDashing(drawRegion);
	}
	else
	{
		Player::m_drawDefault(drawRegion);
	}
	SystemUtils::Rect<int> dest = {
		.x = (int)m_x - 100 - (int)camera.getX(),
		.y = (int)m_y - 100 - (int)camera.getY(),
		.w = 200,
		.h = 200
	};
	SystemUtils::renderCopy(m_texture, drawRegion, dest); //SDL_RenderCopy(renderer.getRawPtr(), m_texture.getRawPtr(), &drawRegion, &dest
}
