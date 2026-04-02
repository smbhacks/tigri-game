#include "Collision.h"

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

bool CollisionBox::checkCollision(const CollisionBox& otherCollBox)
{
	// return if this right side is behind other left side
	if (m_x + m_box.xOffs + m_box.width < otherCollBox.m_x + otherCollBox.m_box.xOffs)
		return false;

	// return if this left side is ahead other right side
	if (m_x + m_box.xOffs > otherCollBox.m_x + otherCollBox.m_box.xOffs + otherCollBox.m_box.width)
		return false;

	// return if this top side is below other bottom side
	if (m_y + m_box.yOffs > otherCollBox.m_y + otherCollBox.m_box.yOffs + otherCollBox.m_box.height)
		return false;

	// return if this bottom side is above other top side
	if (m_y + m_box.yOffs + m_box.height < otherCollBox.m_y + otherCollBox.m_box.yOffs)
		return false;

	return true;
}
