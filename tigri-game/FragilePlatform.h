#pragma once
#include "Platform.h"
#include "memtrace.h"

class Player;

/// <summary>
/// Törékeny platformot reprezentáló osztály, amelyről nem lehet pattanni, ha a játékos zuhanással (dash) érkezik rá.
/// </summary>
class FragilePlatform : public Platform
{
public:
	/// <summary>
	/// Konstruktor a törékeny platform sebességének és pozíciójának inicializálásához.
	/// </summary>
	/// <param name="xSpeed">A platform vízszintes sebessége.</param>
	/// <param name="ySpeed">A platform függőleges sebessége.</param>
	/// <param name="xPos">A platform kezdő X koordinátája.</param>
	/// <param name="yPos">A platform kezdő Y koordinátája.</param>
	FragilePlatform(float xSpeed, float ySpeed, float xPos, float yPos)
		: Platform(xSpeed, ySpeed, xPos, yPos)
	{ }

	/// <summary>Képkockánként lefutó frissítési logika, amely alkalmazza a fizikát.</summary>
	void tick() override;

	/// <summary>
	/// Kirajzolja a törékeny platform textúráját a kamerához viszonyítva.
	/// </summary>
	/// <param name="camera">A kamera objektum, amely meghatározza a relatív eltolást.</param>
	void draw(const Camera& camera) override;

	/// <summary>
	/// Meghatározza, hogy a játékos visszapattanhat-e a platformról.
	/// </summary>
	/// <param name="player">A vizsgált játékos objektum.</param>
	/// <returns>Hamis, ha a játékos éppen lefelé dash-el, különben igaz.</returns>
	bool canBounce(const Player& player) override;
};