#include "Platform.h"

void Platform::tick()
{
	m_xSpeed = -0.01f;
	m_applyPhysics();
}

void Platform::draw(const SDLW_Renderer& renderer)
{

}