#pragma once
class FloatCalcs
{
public:
	static bool relativeEquality(float left, float right);
	static bool relativeEquality(float left, float right, float maxDiff);
	static inline bool isZero(float val);
	static inline bool isNaN(float val);
private:
	FloatCalcs();
};

#include "FloatCalcs-inl.h";