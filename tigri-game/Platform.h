#pragma once
#include "Entity.h"
#include "SDLW.h"

class Platform : public Entity, private Debuggable
{
public:
	Platform(Box collBox)
		: Entity(collBox)
		, Debuggable("Platform")
	{ 
		m_x = 200;
		m_y = 600;
	}
	void tick() override;
	void draw(const SDLW_Renderer& renderer) override;
};