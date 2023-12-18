#include "Vector2D.hpp"
//Note most of the functions/constructors were implemented in the header because it's cleaner and easier to visualize.

Vector2D Vector2D::normalize() {
	float magSquared = magnitudeSquared();
	if (magSquared > 0.0f) {
		x *= q_sqrt(magSquared);
		y *= q_sqrt(magSquared);
	}

	return *this;
}

float Vector2D::q_sqrt(float number) {
	//This is a fast approximation of the square root function.
	//Source: https://en.wikipedia.org/wiki/Fast_inverse_square_root
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	// y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

  	return y;
}