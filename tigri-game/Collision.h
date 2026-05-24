#pragma once
#include "Box.h"
#include "Debuggable.h"
#include "memtrace.h"

/// <summary>
/// Ütközési dobozt reprezentáló osztály, amely dinamikusan követi egy entitás pozícióját.
/// </summary>
class CollisionBox : private Debuggable
{
private:
	float& m_x;
	float& m_y;
	Box m_box;

public:
	/// <summary>
	/// Konstruktor az ütközési doboz inicializálásához.
	/// </summary>
	/// <param name="x">Az entitás X koordinátájának referenciája.</param>
	/// <param name="y">Az entitás Y koordinátájának referenciája.</param>
	/// <param name="box">A helyi eltolásokat és méreteket tartalmazó Box objektum.</param>
	CollisionBox(float& x, float& y, Box& box)
		: Debuggable("CollisionBox")
		, m_x(x)
		, m_y(y)
		, m_box(box)
	{ }

	/// <summary>
	/// Megvizsgálja, hogy a két megadott ütközési doboz fedi-e egymást.
	/// </summary>
	/// <param name="collBox1">Az első vizsgált ütközési doboz.</param>
	/// <param name="collBox2">A második vizsgált ütközési doboz.</param>
	/// <returns>Igaz, ha a két doboz metszi egymást, egyébként hamis.</returns>
	static bool checkCollision(const CollisionBox& collBox1, const CollisionBox& collBox2);

	/// <summary>
	/// Visszaadja a doboz helyi méreteit és eltolásait tartalmazó objektumot.
	/// </summary>
	Box& getBox() { return m_box; }
};