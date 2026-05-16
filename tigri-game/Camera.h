#pragma once
#include "Debuggable.h"

class Camera : private Debuggable
{
private:
	float m_x = 0;
	float m_y = 0;

public:
	Camera()
		: Debuggable("Camera")
	{ }
	float getX() const { return m_x; }
	float getY() const { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
};