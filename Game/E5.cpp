#include "E5.hpp"
#include "UnitEnemy.hpp"
#include "WeaponRapidFire.hpp"

E5::E5(SDL_Renderer* renderer, Vector2D setPos) :  UnitEnemy(renderer, setPos, UnitEnemy::listTemplateData[4]) {
    speed = 10.0f;
    Unit::weapon = new WeaponRapidFire();
}
