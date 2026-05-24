#pragma once
#include "Debuggable.h"
#include "memtrace.h"

/// <summary>
/// A kamera 2D-s pozícióját nyilvántartó és kezelő osztály.
/// </summary>
class Camera : private Debuggable
{
private:
	float m_x = 0;
	float m_y = 0;

public:
	/// <summary>
	/// Alapértelmezett konstruktor, (0, 0) pozícióban hozza létre a kamerát.
	/// </summary>
	Camera()
		: Debuggable("Camera")
	{ }

	/// <summary>
	/// Visszaadja a kamera aktuális X koordinátáját.
	/// </summary>
	float getX() const { return m_x; }

	/// <summary>
	/// Visszaadja a kamera aktuális Y koordinátáját.
	/// </summary>
	float getY() const { return m_y; }

	/// <summary>
	/// Beállítja a kamera X koordinátáját.
	/// </summary>
	/// <param name="x">Az új X koordináta.</param>
	void setX(float x) { m_x = x; }

	/// <summary>
	/// Beállítja a kamera Y koordinátáját.
	/// </summary>
	/// <param name="y">Az új Y koordináta.</param>
	void setY(float y) { m_y = y; }
};