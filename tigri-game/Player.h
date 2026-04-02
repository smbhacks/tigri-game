#pragma once
#include "Entity.h"
#include "Debuggable.h"

class Player : public Entity, private Debuggable
{
public:
	Player(Box collBox) 
		: Entity(collBox)
		, Debuggable("Player")
	{ }
	void tick() override;
};

