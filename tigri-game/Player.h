#pragma once
#include <vector>
#include "Entity.h"
#include "Platform.h"
#include "Debuggable.h"

class Player : public Entity, private Debuggable
{
private:
	void m_handleControlling();
	void m_handlePhysics();
	void m_tickCollChecks();
	std::vector<std::unique_ptr<Platform>>& m_platformsRef; // needed for coll checks
	bool m_dashingDownwards = false;

public:
	Player(Box collBox, std::vector<std::unique_ptr<Platform>>& platformsRef)
		: Entity(collBox)
		, Debuggable("Player")
		, m_platformsRef(platformsRef)
	{ }
	void tick() override;
};

