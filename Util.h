#include <cmath>

#define M_PI    3.14159265358979323846264338327950288   /* pi */

float EaseIn(float a, float b, float percent)
{
	return (a + (b - a) * pow(percent,2));
}

float EaseInOut(float a, float b, float percent)
{
	return (a + (b - a) * ((-cos(percent*(float)M_PI) / 2.f) + 0.5f));
}

float Distance(float a, float b)
{
	return abs((b - a));
}