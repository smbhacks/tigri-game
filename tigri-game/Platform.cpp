#include "Platform.h"
#include "memtrace.h"

void Platform::tick()
{
	m_applyPhysics();
}

void Platform::draw(const Camera& camera)
{

}