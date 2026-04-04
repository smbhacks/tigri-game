#pragma once

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
};