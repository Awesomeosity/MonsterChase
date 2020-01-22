#pragma once
inline bool FloatCalcs::isZero(float value)
{
	return relativeEquality(value, 0, 0.000000001f);
}

inline bool FloatCalcs::isNaN(float value)
{
	volatile float val = value;
	return val != val;
}