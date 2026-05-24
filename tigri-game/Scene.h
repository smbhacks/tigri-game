#pragma once
#include <iostream>
#include "Debuggable.h"
#include "Controller.h"
#include "memtrace.h"

/// <summary>
/// A játék jeleneteinek (scene) absztrakt alaposztálya.
/// </summary>
class Scene
{
protected:
	bool m_shutdownSceneFlag = false;
public:
	/// <summary>Virtuális destruktor az alaposztályhoz.</summary>
	virtual ~Scene() {};

	/// <summary>Képkockánként lefutó frissítési logika.</summary>
	virtual void tick()
	{
		std::cout << "Scene::tick() -> No scene to tick yet!\n";
	}

	/// <summary>A jelenet kirajzolásáért felelős logika.</summary>
	virtual void draw()
	{
		std::cout << "Scene::draw() -> No scene to draw yet!\n";
	}

	/// <summary>Visszaadja, hogy a jelenet kérte-e a bezárását/leállítását.</summary>
	bool isSceneReadyToShutdown() const { return m_shutdownSceneFlag; }
};