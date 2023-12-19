#include "Vector2D.hpp"
//Note most of the functions/constructors were implemented in the header because it's cleaner and easier to visualize.

Vector2D Vector2D::normalize() {
	float magStored = magnitude();
	if (magStored > 0.0f) {
		x /= magStored;
		y /= magStored;
	}

	return *this;
}
