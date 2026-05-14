#pragma once
#include "Box.h"
#include "Debuggable.h"

class CollisionBox : private Debuggable
{
private:
	float& m_x;
	float& m_y;
	Box m_box;

public:
	CollisionBox(float& x, float& y, Box& box)
		: Debuggable("CollisionBox")
		, m_x(x)
		, m_y(y)
		, m_box(box)
	{ }
	static bool checkCollision(const CollisionBox& collBox1, const CollisionBox& collBox2);
	Box& getBox() { return m_box; }
};
