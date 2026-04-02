#include "Entity.h"

void Entity::move()
{
	m_xSpeed += m_xAcceleration;
	m_ySpeed += m_yAcceleration;
	m_x += m_xSpeed;
	m_y += m_ySpeed;
}