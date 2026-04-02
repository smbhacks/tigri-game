#pragma once
#include "Scene.h"
#include "Entity.h"
#include "Debuggable.h"

class GameplayScene : public Scene, private Debuggable
{
private:
	Entity testentity;

public:
	GameplayScene() 
		: Debuggable("GameplayScene")
		, Scene()
		, testentity(Box(0, 0, 0, 0))
	{ }
	void tick() override;
	void draw() override;
};

