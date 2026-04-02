#pragma once
#include <iostream>
#include "Debuggable.h"

class Scene : private Debuggable
{
public:
	Scene() : Debuggable("Scene") {}
	virtual void draw()
	{
		std::cout << "Scene::draw() -> No scene to draw yet!\n";
	}
};