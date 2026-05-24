#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Platform.h"
#include "Debuggable.h"
#include "SystemUtils.h"
#include "memtrace.h"

/// <summary>
/// A játékos karakterét reprezentáló osztály, amely kezeli az irányítást, a fizikát, az ütközéseket és az animációkat.
/// </summary>
class Player : public Entity, private Debuggable
{
private:
	/// <summary>Feldolgozza a kontrollerből érkező játékosi bemeneteket.</summary>
	void m_handleControlling();

	/// <summary>Kezeli a játékosra ható fizikai erőket, mint a gravitáció és a sebesség korlátozása.</summary>
	void m_handlePhysics();

	/// <summary>Ellenőrzi az ütközéseket a platformokkal, és kezeli a visszapattanást.</summary>
	void m_tickCollChecks();

	/// <summary>Kezeli a lefelé irányuló gyors zuhanás (dash) logikáját és időzítését.</summary>
	void m_handleDash();

	/// <summary>
	/// Kiszámítja a textúra kivágási régióját a zuhanó (dash) animációhoz.
	/// </summary>
	/// <param name="drawRegion">A módosítandó téglalap, amely a textúra kivágását jelöli.</param>
	void m_drawDashing(SystemUtils::Rect<int>& drawRegion);

	/// <summary>
	/// Kiszámítja a textúra kivágási régióját az alapértelmezett (eső) animációhoz.
	/// </summary>
	/// <param name="drawRegion">A módosítandó téglalap, amely a textúra kivágását jelöli.</param>
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
	/// <summary>
	/// Konstruktor a játékos objektum létrehozásához és inicializálásához.
	/// </summary>
	/// <param name="x">A játékos kezdő X koordinátája.</param>
	/// <param name="y">A játékos kezdő Y koordinátája.</param>
	/// <param name="collBox">A játékos ütközési doboza.</param>
	/// <param name="platformsRef">Referencia a pályán lévő platformok listájára (ütközésvizsgálathoz).</param>
	/// <param name="pngPath">A játékos sprite textúrájának elérési útja.</param>
	Player(float x, float y, Box collBox, std::vector<std::unique_ptr<Platform>>& platformsRef, const char* pngPath)
		: Entity(collBox, x, y)
		, Debuggable("Player")
		, m_platformsRef(platformsRef)
		, m_texture(pngPath)
	{ }

	/// <summary>
	/// Képkockánként lefutó frissítési logika, amely összefogja az irányítást, fizikát és ütközéseket.
	/// </summary>
	void tick() override;

	/// <summary>
	/// Kirajzolja a játékos aktuális animációs képkockáját a kamerához viszonyítva.
	/// </summary>
	/// <param name="camera">A kamera objektum, amely meghatározza a relatív eltolást.</param>
	void draw(const Camera& camera) override;

	/// <summary>Visszaadja, hogy a játékos éppen egy lefelé irányuló zuhanó támadást (dash) hajt-e végre.</summary>
	bool isDashingDownwards() const { return m_dashingDownwards; }

	/// <summary>Visszaadja, hogy a játékos kiesett-e a pályáról (meghalt).</summary>
	bool hasDied() const { return m_died; }
};