#pragma once

#include "Ogre.h"
#include <limits>
#include <stdint.h>

typedef Ogre::Real Decimal;
typedef int64_t HashKey; 

const Decimal EPSILON = std::numeric_limits<Decimal>::min();

enum Axis : int
{
	X = 0, //x axis
	Y, //y axis
	Z  //z axis
};

struct Type_Info_Cmp
{
public:
	int operator()(const std::type_info* a, const std::type_info *b)const
	{
		return a->before(*b);
	}
};


enum Concatenation : int
{
	XYZ = 0,
	XZY,

	YXZ,
	YZX,

	ZXY,
	ZYX
};