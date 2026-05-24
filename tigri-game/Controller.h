#pragma once
#include "Debuggable.h"
#include "memtrace.h"

/// <summary>
/// A lehetséges játékvezérlő gombokat reprezentáló felsorolás.
/// </summary>
enum Key
{
	Right,
	Left,
	Down,
	Up,
	Confirm,
	Select
};

/// <summary>
/// A játékos bemeneteit kezelő és tároló osztály.
/// </summary>
class Controller : private Debuggable
{
private:
	bool m_pressingRight = false;
	bool m_pressingLeft = false;
	bool m_pressingDown = false;
	bool m_pressingUp = false;
	bool m_pressingConfirm = false;
	bool m_pressingSelect = false;
	bool m_pressedRightLastTick = false;
	bool m_pressedLeftLastTick = false;
	bool m_pressedDownLastTick = false;
	bool m_pressedUpLastTick = false;
	bool m_pressedConfirmLastTick = false;
	bool m_pressedSelectLastTick = false;

public:
	/// <summary>
	/// Alapértelmezett konstruktor.
	/// </summary>
	Controller()
		: Debuggable("Controller")
	{
	}

	/// <summary>
	/// Eltárolja az aktuális gombnyomásokat a következő képkockára (tickre).
	/// </summary>
	void setPrevs();

	/// <summary>
	/// Frissíti egy adott gomb lenyomási állapotát.
	/// </summary>
	/// <param name="key">A frissítendő gomb.</param>
	/// <param name="pressedState">A gomb új állapota (igaz, ha le van nyomva).</param>
	void handleInput(Key key, bool pressedState);

	/// <summary>Visszaadja, hogy a Jobb gomb éppen le van-e nyomva.</summary>
	bool isPressingRight() const { return m_pressingRight; };
	/// <summary>Visszaadja, hogy a Bal gomb éppen le van-e nyomva.</summary>
	bool isPressingLeft() const { return m_pressingLeft; };
	/// <summary>Visszaadja, hogy a Le gomb éppen le van-e nyomva.</summary>
	bool isPressingDown() const { return m_pressingDown; };
	/// <summary>Visszaadja, hogy a Fel gomb éppen le van-e nyomva.</summary>
	bool isPressingUp() const { return m_pressingUp; };
	/// <summary>Visszaadja, hogy az Elfogadás (Confirm) gomb éppen le van-e nyomva.</summary>
	bool isPressingConfirm() const { return m_pressingConfirm; }
	/// <summary>Visszaadja, hogy a Kiválasztás (Select) gomb éppen le van-e nyomva.</summary>
	bool isPressingSelect() const { return m_pressingSelect; }

	/// <summary>Visszaadja, hogy a Jobb gomb le volt-e nyomva az előző tickben.</summary>
	bool pressedRightLastTick() const { return m_pressedRightLastTick; }
	/// <summary>Visszaadja, hogy a Bal gomb le volt-e nyomva az előző tickben.</summary>
	bool pressedLeftLastTick() const { return m_pressedLeftLastTick; }
	/// <summary>Visszaadja, hogy a Le gomb le volt-e nyomva az előző tickben.</summary>
	bool pressedDownLastTick() const { return m_pressedDownLastTick; }
	/// <summary>Visszaadja, hogy a Fel gomb le volt-e nyomva az előző tickben.</summary>
	bool pressedUpLastTick() const { return m_pressedUpLastTick; }
	/// <summary>Visszaadja, hogy az Elfogadás gomb le volt-e nyomva az előző tickben.</summary>
	bool pressedConfirmLastTick() const { return m_pressedConfirmLastTick; }
	/// <summary>Visszaadja, hogy a Kiválasztás gomb le volt-e nyomva az előző tickben.</summary>
	bool pressedSelectLastTick() const { return m_pressedSelectLastTick; }
};