#pragma once
class FloatCalcs
{
public:
	static bool relativeEquality(float left, float right);
	static bool relativeEquality(float left, float right, float maxDiff);
private:
	FloatCalcs();
};

