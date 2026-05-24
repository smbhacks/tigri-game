#pragma once
#include "Entity.h"
#include "Camera.h"
#include "SystemUtils.h"
#include "memtrace.h"

class Player;

/// <summary>
/// A játékban szereplő ugrófelületek (platformok) absztrakt alaposztálya.
/// </summary>
class Platform : public Entity
{
protected:
	SystemUtils::Texture m_texture;

public:
	/// <summary>
	/// Konstruktor a platform sebességének és pozíciójának inicializálásához.
	/// </summary>
	/// <param name="xSpeed">A platform vízszintes sebessége.</param>
	/// <param name="ySpeed">A platform függőleges sebessége.</param>
	/// <param name="xPos">A platform kezdő X koordinátája.</param>
	/// <param name="yPos">A platform kezdő Y koordinátája.</param>
	Platform(float xSpeed, float ySpeed, float xPos, float yPos)
		: Entity(Box(0, 0, 100, 8))
		, m_texture("src/platforms.png")
	{
		m_xSpeed = xSpeed;
		m_ySpeed = ySpeed;
		m_x = xPos;
		m_y = yPos;
	}

	/// <summary>Virtuális destruktor az alaposztályhoz.</summary>
	virtual ~Platform() = default;

	/// <summary>
	/// Meghatározza, hogy a játékos visszapattanhat-e erről a platformról (leszármazottakban implementálandó).
	/// </summary>
	/// <param name="player">A játékos objektum referenciája.</param>
	/// <returns>Igaz, ha a játékos visszapattanhat, egyébként hamis.</returns>
	virtual bool canBounce(const Player& player) = 0;
};