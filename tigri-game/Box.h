#pragma once
#include "Debuggable.h"
#include "memtrace.h"

class Box : private Debuggable
{
public:
	float xOffs;
	float yOffs;
	float width;
	float height;
	Box(float xOffs, float yOffs, float width, float height) 
		: Debuggable("Box")
		, xOffs(xOffs)
		, yOffs(yOffs)
		, width(width)
		, height(height)
	{}
};