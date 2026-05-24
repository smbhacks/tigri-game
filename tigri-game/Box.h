#pragma once
#include "Debuggable.h"
#include "memtrace.h"

/// <summary>
/// Egy 2D dobozt (vagy határoló téglalapot) reprezentáló osztály.
/// </summary>
class Box : private Debuggable
{
public:
	float xOffs;
	float yOffs;
	float width;
	float height;

	/// <summary>
	/// Konstruktor a doboz pozíciójának és méreteinek inicializálásához.
	/// </summary>
	/// <param name="xOffs">Az X tengely menti eltolás (pozíció).</param>
	/// <param name="yOffs">Az Y tengely menti eltolás (pozíció).</param>
	/// <param name="width">A doboz szélessége.</param>
	/// <param name="height">A doboz magassága.</param>
	Box(float xOffs, float yOffs, float width, float height)
		: Debuggable("Box")
		, xOffs(xOffs)
		, yOffs(yOffs)
		, width(width)
		, height(height)
	{ }
};