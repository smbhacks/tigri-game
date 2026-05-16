#pragma once
#include <iostream>
#include "Debuggable.h"
#include "Controller.h"

class Scene
{
public:
	virtual ~Scene() {};
	virtual void tick()
	{
		std::cout << "Scene::tick() -> No scene to tick yet!\n";
	}
	virtual void draw()
	{
		std::cout << "Scene::draw() -> No scene to draw yet!\n";
	}
};