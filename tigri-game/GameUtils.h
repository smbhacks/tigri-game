#pragma once
#include <cstdlib>
#include <stdexcept>
#include "memtrace.h"

/// <summary>
/// Ellenőrzi, hogy a megadott intervallum érvényes-e. Kivételt dob, ha az alsó határ nagyobb vagy egyenlő, mint a felső.
/// </summary>
/// <param name="inclusiveLower">Az intervallum alsó, zárt határa.</param>
/// <param name="exclusiveUpper">Az intervallum felső, nyílt határa.</param>
template<typename T>
static void assertInterval(const T& inclusiveLower, const T& exclusiveUpper)
{
	if (inclusiveLower >= exclusiveUpper)
		throw std::invalid_argument("Got an inclusiveLower that's greater or equal to exclusiveUpper. That is an empty set.");
}

namespace GameUtils
{
	/// <summary>
	/// Egy értéket a megadott alsó és felső korlátok közé szorít.
	/// </summary>
	/// <param name="value">A korlátozandó érték.</param>
	/// <param name="lowerBound">Az alsó megengedett korlát.</param>
	/// <param name="upperBound">A felső megengedett korlát.</param>
	/// <returns>A korlátok közé szorított érték.</returns>
	template<typename T>
	const T& clamp(const T& value, const T& lowerBound, const T& upperBound)
	{
		return (value < lowerBound) ? lowerBound : (value > upperBound) ? upperBound : value;
	}

	/// <summary>
	/// Visszaadja a megadott érték előjelét.
	/// </summary>
	/// <param name="value">A vizsgálandó érték.</param>
	/// <returns>-1, ha negatív; 1, ha pozitív; 0, ha nulla.</returns>
	template<typename T>
	int sign(const T& value)
	{
		return value < 0 ? -1 : (value > 0) ? 1 : 0;
	}

	/// <summary>
	/// Megkeres egy elemet a megadott iterátorok által meghatározott tartományban.
	/// </summary>
	/// <param name="haystackStart">A keresési tartomány kezdete.</param>
	/// <param name="haystackEnd">A keresési tartomány vége.</param>
	/// <param name="needle">A keresett elem.</param>
	/// <returns>Az iterátor a megtalált elemre, vagy a haystackEnd, ha az elem nem található.</returns>
	template<typename Iterator, typename T>
	Iterator find(Iterator haystackStart, Iterator haystackEnd, const T& needle)
	{
		for (Iterator it = haystackStart; it != haystackEnd; it++)
		{
			if (*it == needle)
				return it;
		}
		return haystackEnd;
	}

	/// <summary>
	/// Beállítja a véletlenszám-generátor kezdőértékét (seed).
	/// </summary>
	/// <param name="seed">A beállítandó kezdőérték.</param>
	inline void setRandomSeed(unsigned int seed)
	{
		srand(seed);
	}

	/// <summary>
	/// Generál egy véletlenszámot a megadott intervallumban (alapértelmezett típusokhoz).
	/// </summary>
	/// <param name="inclusiveLower">Az alsó, zárt határ.</param>
	/// <param name="exclusiveUpper">A felső, nyílt határ.</param>
	/// <returns>A generált véletlenszám.</returns>
	template<typename T>
	inline T getRandomNum(T inclusiveLower, T exclusiveUpper)
	{
		assertInterval(inclusiveLower, exclusiveUpper);
		return inclusiveLower + rand() % exclusiveUpper;
	}

	/// <summary>
	/// Generál egy lebegőpontos véletlenszámot a megadott intervallumban (float specializáció).
	/// </summary>
	/// <param name="inclusiveLower">Az alsó, zárt határ.</param>
	/// <param name="exclusiveUpper">A felső, nyílt határ.</param>
	/// <returns>A generált lebegőpontos véletlenszám.</returns>
	template<>
	inline float getRandomNum(float inclusiveLower, float exclusiveUpper)
	{
		assertInterval(inclusiveLower, exclusiveUpper);
		float scale = rand() / float(RAND_MAX);
		return inclusiveLower + scale * (exclusiveUpper - inclusiveLower);
	}
};