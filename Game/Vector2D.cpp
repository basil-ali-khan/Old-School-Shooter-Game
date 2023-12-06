<<<<<<< Updated upstream
#include "Vector2D.hpp"
//Note most of the functions/constructors were implemented in the header because it's cleaner and easier to visualize.


Vector2D Vector2D::normalize() {
	float magnitudeStored = magnitude();
	if (magnitudeStored > 0.0f) {
		x /= magnitudeStored;
		y /= magnitudeStored;
	}

	return *this;
=======
#include "Vector2D.hpp"
//Note most of the functions/constructors were implemented in the header because it's cleaner and easier to visualize.


Vector2D Vector2D::normalize() {
	float magnitudeStored = magnitude();
	if (magnitudeStored > 0.0f) {
		x /= magnitudeStored;
		y /= magnitudeStored;
	}

	return *this;
>>>>>>> Stashed changes
}