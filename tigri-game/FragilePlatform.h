#pragma once
#include "Platform.h"
#include "memtrace.h"

class Player;

class FragilePlatform : public Platform
{
public:
	FragilePlatform(float xSpeed, float ySpeed, float xPos, float yPos)
		: Platform(xSpeed, ySpeed, xPos, yPos)
	{
	}
	void tick() override;
	void draw(const Camera& camera) override;
	bool canBounce(const Player& player) override;
};
