#pragma once
#include <vector>
#include "Entity.h"
#include "Platform.h"
#include "Debuggable.h"
#include "SDLW.h"
#include "SDL.h"

class Player : public Entity, private Debuggable
{
private:
	void m_handleControlling();
	void m_handlePhysics();
	void m_tickCollChecks();
	void m_handleDash();
	void m_drawDashing(SDL_Rect& drawRegion);
	void m_drawDefault(SDL_Rect& drawRegion);
	std::vector<std::unique_ptr<Platform>>& m_platformsRef; // needed for coll checks
	bool m_dashingDownwards = false;
	bool m_dashCounterOngoing = false;
	int m_dashCounter = 0;
	bool m_fallingStarted = false;
	int m_fallingCounter = 0;
	SDLW_Texture m_texture;

public:
	Player(Box collBox, std::vector<std::unique_ptr<Platform>>& platformsRef)
		: Entity(collBox)
		, Debuggable("Player")
		, m_platformsRef(platformsRef)
		, m_texture("src/player.png")
	{ }
	void tick() override;
	void draw(const SDLW_Renderer& renderer) override;
};

