#pragma once
#include <cstdlib>
#include <stdexcept>

template<typename T> 
static void assertInterval(const T& inclusiveLower, const T& exclusiveUpper)
{
	if (inclusiveLower >= exclusiveUpper)
		throw std::invalid_argument("Got an inclusiveLower that's greater or equal to exclusiveUpper. That is an empty set.");
}

namespace GameUtils
{
	template<typename T>
	const T& clamp(const T& value, const T& lowerBound, const T& upperBound)
	{
		return (value < lowerBound) ? lowerBound : (value > upperBound) ? upperBound : value;
	}

	template<typename T>
	int sign(const T& value)
	{
		return value < 0 ? -1 : (value > 0) ? 1 : 0;
	}

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

	inline void setRandomSeed(unsigned int seed)
	{
		srand(seed);
	}

	template<typename T>
	inline T getRandomNum(T inclusiveLower, T exclusiveUpper)
	{
		assertInterval(inclusiveLower, exclusiveUpper);
		return inclusiveLower + rand() % exclusiveUpper;
	}
	template<>
	inline float getRandomNum(float inclusiveLower, float exclusiveUpper)
	{
		assertInterval(inclusiveLower, exclusiveUpper);
		float scale = rand() / float(RAND_MAX);
		return inclusiveLower + scale * (exclusiveUpper - inclusiveLower);
	}
};