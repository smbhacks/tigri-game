#pragma once
#include <vector>
#include "Entity.h"
#include "Platform.h"
#include "Debuggable.h"

class Player : public Entity, private Debuggable
{
private:
	void m_tickPhysics();
	void m_tickCollChecks();
	std::vector<std::unique_ptr<Platform>>& m_platformsRef; // needed for coll checks

public:
	Player(Box collBox, std::vector<std::unique_ptr<Platform>>& platformsRef)
		: Entity(collBox)
		, Debuggable("Player")
		, m_platformsRef(platformsRef)
	{ }
	void tick() override;
};

