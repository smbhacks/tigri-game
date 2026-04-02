#pragma once
#include "Entity.h"

class Platform : public Entity, private Debuggable
{
public:
	Platform(Box collBox)
		: Entity(collBox)
		, Debuggable("Platform")
	{ 
		m_x = 1280;
	}
	void tick() override;
};