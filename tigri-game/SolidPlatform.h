#pragma once
#include "Platform.h"

class Player;

class SolidPlatform : public Platform
{
public:
	SolidPlatform(float xSpeed, float ySpeed, float xPos, float yPos)
		: Platform(xSpeed, ySpeed, xPos, yPos)
	{ }
	void tick() override;
	void draw(const Camera& camera) override;
	bool canBounce(const Player& player) override { return true; }
};
