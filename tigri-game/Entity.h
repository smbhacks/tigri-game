#pragma once
#include "Collision.h"
#include "Debuggable.h"
#include "Scene.h"
#include "Camera.h"
#include "memtrace.h"

/// <summary>
/// Játékbeli entitások (mozgás, pozíció, ütközés) absztrakt alaposztálya.
/// </summary>
class Entity
{
protected:
	float m_x = 0;
	float m_y = 0;
	float m_xSpeed = 0;
	float m_ySpeed = 0;
	float m_xAcceleration = 0;
	float m_yAcceleration = 0;
	CollisionBox m_collBox;

	/// <summary>
	/// Frissíti a sebességet a gyorsulás alapján, és a pozíciót a sebesség alapján.
	/// </summary>
	void m_applyPhysics();

public:
	/// <summary>
	/// Konstruktor alapértelmezett (0, 0) pozícióval és megadott ütközési dobozzal.
	/// </summary>
	/// <param name="collBox">Az entitás helyi ütközési doboza.</param>
	Entity(Box collBox)
		: m_collBox(m_x, m_y, collBox)
	{ }

	/// <summary>
	/// Konstruktor megadott kezdőpozícióval és ütközési dobozzal.
	/// </summary>
	/// <param name="collBox">Az entitás helyi ütközési doboza.</param>
	/// <param name="x">Kezdő X koordináta.</param>
	/// <param name="y">Kezdő Y koordináta.</param>
	Entity(Box collBox, float x, float y)
		: m_x(x)
		, m_y(y)
		, m_collBox(m_x, m_y, collBox)
	{ }

	/// <summary>
	/// Virtuális destruktor az alaposztályhoz.
	/// </summary>
	virtual ~Entity() = default;

	/// <summary>
	/// Képkockánként lefutó frissítési logika (leszármazottakban implementálandó).
	/// </summary>
	virtual void tick() = 0;

	/// <summary>
	/// Kirajzolja az ütközési dobozt és a középpontot hibakeresési (debug) célból.
	/// </summary>
	/// <param name="camera">A kamera, amihez képest a rajzolás történik.</param>
	void drawCollBox(const Camera& camera);

	/// <summary>
	/// Kirajzolja az entitást a képernyőre (leszármazottakban implementálandó).
	/// </summary>
	/// <param name="camera">A kamera, amihez képest a rajzolás történik.</param>
	virtual void draw(const Camera& camera) = 0;

	/// <summary>
	/// Megadja, hogy az entitás mennyire lóg ki a képernyőről vízszintesen.
	/// </summary>
	/// <param name="camera">A kamera aktuális pozíciója.</param>
	/// <returns>A képernyőről való lelógás mértéke, vagy 0, ha a képernyőn belül van.</returns>
	float howOffscreenX(const Camera& camera);

	/// <summary>Visszaadja az entitás ütközési dobozának referenciáját.</summary>
	CollisionBox& getCollBox() { return m_collBox; }

	/// <summary>Visszaadja az entitás Y koordinátáját.</summary>
	float getY() const { return m_y; }

	/// <summary>Visszaadja az entitás X koordinátáját.</summary>
	float getX() const { return m_x; }
};