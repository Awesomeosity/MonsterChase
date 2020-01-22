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

void FloatCalcs::floatingUnitTest()
{
	assert(isZero(0.0f));
	assert(!isZero(0.01f));
	assert(!isZero(0.00000001f));

	assert(!isNaN(0.0f));
	assert(!isNaN(-0.0f));

	assert(relativeEquality(0.1f, 0.1f));
	assert(!relativeEquality(0.01f, 0.011f));
	assert(!relativeEquality(1.1f, 1.11f));
}