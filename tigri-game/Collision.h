#pragma once
#include "Box.h"
#include "Debuggable.h"

//	struct Vec2D
//	{
//		// origin is collision box's top left point
//		float x;
//		float y;
//	};
//	
//	struct CollisionResult
//	{
//		Vec2D topLeft;
//		Vec2D topRight;
//		Vec2D bottomLeft;
//		Vec2D bottomRight;
//	
//		bool topLeftCollided = false;
//		bool topRightCollided = false;
//		bool bottomLeftCollided = false;
//		bool bottomRightCollided = false;
//	};

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
	bool checkCollision(const CollisionBox& otherCollBox);
	Box& getBox() { return m_box; }
};
