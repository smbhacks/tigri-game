#pragma once
#include "GameplayScene.h"

class MediumGameplayScene : public GameplayScene
{
public:
	MediumGameplayScene()
		: GameplayScene("src/medium/player.png")
	{ }
	void draw() override;
};

