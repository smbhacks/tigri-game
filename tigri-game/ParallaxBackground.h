#pragma once
#include "Camera.h"
#include "SystemUtils.h"
#include "memtrace.h"

/// <summary>
/// Többrétegű háttérkezelő osztály, amely a rétegeket eltérő sebességgel mozgatja.
/// </summary>
class ParallaxBackground
{
private:
	SystemUtils::Texture m_layer1;
	SystemUtils::Texture m_layer2;
	SystemUtils::Texture m_layer3;
	SystemUtils::Texture m_layer4;
	SystemUtils::Texture m_bgGradient;

	/// <summary>
	/// Kirajzol egy adott háttérréteget a kamera pozíciója és a sebességszorzó alapján.
	/// </summary>
	/// <param name="texture">A rajzolandó textúra réteg.</param>
	/// <param name="camera">A kamera objektum.</param>
	/// <param name="speedMultiplier">A réteg mozgási sebességének szorzója.</param>
	void m_drawLayer(const SystemUtils::Texture& texture, const Camera& camera, float speedMultiplier);

public:
	/// <summary>
	/// Konstruktor a háttér textúráinak betöltéséhez.
	/// </summary>
	/// <param name="bggradient">A leghátsó statikus színátmenet textúra útvonala.</param>
	/// <param name="layer1">Az 1. mozgó réteg textúra útvonala.</param>
	/// <param name="layer2">A 2. mozgó réteg textúra útvonala.</param>
	/// <param name="layer3">A 3. mozgó réteg textúra útvonala.</param>
	/// <param name="layer4">A 4. mozgó réteg textúra útvonala.</param>
	ParallaxBackground(const char* bggradient, const char* layer1, const char* layer2, const char* layer3, const char* layer4)
		: m_layer1(layer1)
		, m_layer2(layer2)
		, m_layer3(layer3)
		, m_layer4(layer4)
		, m_bgGradient(bggradient)
	{ }

	/// <summary>
	/// Kirajzolja az összes háttérréteget a kamerához viszonyítva.
	/// </summary>
	/// <param name="camera">A kamera objektum.</param>
	void draw(const Camera& camera);
};