#pragma once
#include "Platform.h"
#include "memtrace.h"

class Player;

/// <summary>
/// Szilárd platformot reprezentáló osztály, amelyről a játékos minden esetben visszapattan.
/// </summary>
class SolidPlatform : public Platform
{
public:
	/// <summary>
	/// Konstruktor a szilárd platform sebességének és pozíciójának inicializálásához.
	/// </summary>
	/// <param name="xSpeed">A platform vízszintes sebessége.</param>
	/// <param name="ySpeed">A platform függőleges sebessége.</param>
	/// <param name="xPos">A platform kezdő X koordinátája.</param>
	/// <param name="yPos">A platform kezdő Y koordinátája.</param>
	SolidPlatform(float xSpeed, float ySpeed, float xPos, float yPos)
		: Platform(xSpeed, ySpeed, xPos, yPos)
	{ }

	/// <summary>Képkockánként lefutó frissítési logika, amely alkalmazza a fizikát.</summary>
	void tick() override;

	/// <summary>
	/// Kirajzolja a szilárd platform textúráját a kamerához viszonyítva.
	/// </summary>
	/// <param name="camera">A kamera objektum, amely meghatározza a relatív eltolást.</param>
	void draw(const Camera& camera) override;

	/// <summary>
	/// Meghatározza, hogy a játékos visszapattanhat-e a platformról.
	/// </summary>
	/// <param name="player">A vizsgált játékos objektum.</param>
	/// <returns>Szilárd platform lévén mindig igazat (visszapattanást) ad vissza.</returns>
	bool canBounce(const Player& player) override { return true; }
};