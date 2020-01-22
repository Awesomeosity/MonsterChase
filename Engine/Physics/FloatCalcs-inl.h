#include "FloatCalcs.h"
#pragma once
inline bool FloatCalcs::isZero(const float value)
{
	return relativeEquality(value, 0, 0.000000001f);
}

inline bool FloatCalcs::isNaN(const float value)
{
	volatile float val = value;
	return val != val;
}