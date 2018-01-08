#include <cmath>

#define M_PI    3.14159265358979323846264338327950288   /* pi */

float EaseIn(float a, float b, float percent)
{
	return (a + (b - a) * pow(percent, 2));
}

float EaseInOut(float a, float b, float percent)
{
	return (a + (b - a) * ((-cos(percent*(float)M_PI) / 2.f) + 0.5f));
}

float Distance(float a, float b)
{
	return abs((b - a));
}

SDL_Color InterpolateColors(const SDL_Color& c1, const SDL_Color& c2)
{
	SDL_Color c = c1;
	if (c1.r > c2.r) --c.r;
	else if (c1.r < c2.r) ++c.r;
	if (c1.g > c2.g) --c.g;
	else if (c1.g < c2.g) ++c.g;
	if (c1.b > c2.b) --c.b;
	else if (c1.b < c2.b) ++c.b;

	return c;
}

bool SameColor(const SDL_Color& c1, const SDL_Color& c2)
{
	return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}