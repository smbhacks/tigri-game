#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Platform.h"
#include "Debuggable.h"
#include "SystemUtils.h"
#include "memtrace.h"

class Player : public Entity, private Debuggable
{
private:
	void m_handleControlling();
	void m_handlePhysics();
	void m_tickCollChecks();
	void m_handleDash();
	void m_drawDashing(SystemUtils::Rect<int>& drawRegion);
	void m_drawDefault(SystemUtils::Rect<int>& drawRegion);
	std::vector<std::unique_ptr<Platform>>& m_platformsRef; // needed for coll checks
	bool m_dashingDownwards = false;
	bool m_dashCounterOngoing = false;
	int m_dashCounter = 0;
	bool m_fallingStarted = false;
	int m_fallingCounter = 0;
	bool m_lowerGravityAllowed = false;
	float m_gravity = 0;
	SystemUtils::Texture m_texture;
	bool m_died = false;

public:
	Player(float x, float y, Box collBox, std::vector<std::unique_ptr<Platform>>& platformsRef, const char* pngPath)
		: Entity(collBox, x, y)
		, Debuggable("Player")
		, m_platformsRef(platformsRef)
		, m_texture(pngPath)
	{ }
	void tick() override;
	void draw(const Camera& camera) override;
	bool isDashingDownwards() const { return m_dashingDownwards; }
	bool hasDied() const { return m_died; }
};

