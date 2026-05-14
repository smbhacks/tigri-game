#include "Collision.h"
#include "memtrace.h"

//	Vec2D setCollDistance(const Vec2D& thisVec, const Vec2D& otherVec, bool& collidedRef)
//	{
//		Vec2D result;
//	
//		result.x = otherVec.x - thisVec.x;
//		result.y = otherVec.y - thisVec.y;
//	
//		if (result.x < 0 && result.y < 0)
//			collidedRef = false;
//		else
//			collidedRef = true;
//	
//		return result;
//	}

bool CollisionBox::checkCollision(const CollisionBox& collBox1, const CollisionBox& collBox2)
{
	// return if this right side is behind other left side
	if (collBox1.m_x + collBox1.m_box.xOffs + collBox1.m_box.width <= collBox2.m_x + collBox2.m_box.xOffs)
		return false;

	// return if this left side is ahead other right side
	if (collBox1.m_x + collBox1.m_box.xOffs >= collBox2.m_x + collBox2.m_box.xOffs + collBox2.m_box.width)
		return false;

	// return if this top side is below other bottom side
	if (collBox1.m_y + collBox1.m_box.yOffs >= collBox2.m_y + collBox2.m_box.yOffs + collBox2.m_box.height)
		return false;

	// return if this bottom side is above other top side
	if (collBox1.m_y + collBox1.m_box.yOffs + collBox1.m_box.height <= collBox2.m_y + collBox2.m_box.yOffs)
		return false;

	return true;
}
