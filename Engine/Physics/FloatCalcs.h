#pragma once
class FloatCalcs
{
public:
	static bool relativeEquality(const float left, const float right);
	static bool relativeEquality(const float left, const float right, const float maxDiff);
	static inline bool isZero(const float val);
	static inline bool isNaN(const float val);

	static void floatingUnitTest();
private:
	FloatCalcs();
};

#include "FloatCalcs-inl.h"