#include "Platform.h"

void Platform::tick()
{
	m_xSpeed = -1.5f;
	m_applyPhysics();
}
