#include "Vector2D.h"
//Note most of the functions/constructors were implemented in the header because it's cleaner and easier to visualize.

Vector2D Vector2D::normalize() {

	float magnitudeSquared = x * x + y * y;
	if (magnitudeSquared > 0.0f) {
		float invSqrt = Q_rsqrt(magnitudeSquared);
		x *= invSqrt;
		y *= invSqrt;
	}

	return *this;
}

float Vector2D::Q_rsqrt(float number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));

	return y;
}