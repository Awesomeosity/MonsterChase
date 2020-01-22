#include "FloatCalcs.h"
#include <math.h>
#include <cassert>

bool FloatCalcs::relativeEquality(const float left, const float right)
{
	return relativeEquality(left, right, 0.0001f);
}

bool FloatCalcs::relativeEquality(const float left, const float right, const float maxDiff)
{
	if (left == right)
	{
		return true;
	}

	float intern_left, intern_right;
	float diff = static_cast<float>(fabs(static_cast<double>(left) - static_cast<double>(right)));
	intern_left = static_cast<float>(fabs(static_cast<double>(left)));
	intern_right = static_cast<float>(fabs(static_cast<double>(right)));

	float largest = (intern_right > intern_left) ? intern_right : intern_left;

	if (diff <= largest * maxDiff)
	{
		return true;
	}

	return false;
}