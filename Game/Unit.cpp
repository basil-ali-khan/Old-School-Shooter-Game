#include "Unit.h"



Unit::Unit(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture, int setHealthMax, Weapon setWeapon) :
	Sprite(renderer, setPos, filenameForTexture, 0.5f/2), healthMax(setHealthMax), weapon(setWeapon) {

}

void Unit::update(float dT) {
    //Update the weapon.
    weapon.update(dT);
}


bool Unit::isAlive() {
	return (healthCurrent > 0);
}
