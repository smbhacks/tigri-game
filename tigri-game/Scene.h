#pragma once
#include <iostream>
#include "Debuggable.h"
#include "SDLW.h"
#include "Controller.h"

struct Camera : private Debuggable
{
	float x = 0;
	float y = 0;
	Camera()
		: Debuggable("Camera")
	{ }
};

class Scene
{
public:
	virtual ~Scene() {};
	virtual void tick()
	{
		std::cout << "Scene::tick() -> No scene to tick yet!\n";
	}
	virtual void draw(const SDLW_Renderer& renderer)
	{
		std::cout << "Scene::draw() -> No scene to draw yet!\n";
	}
};