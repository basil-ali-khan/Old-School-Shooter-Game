#include "E4.hpp"
#include "UnitEnemy.hpp"
#include "WeaponRapidFire.hpp"

E4::E4(SDL_Renderer* renderer, Vector2D setPos) :  UnitEnemy(renderer, setPos, UnitEnemy::listTemplateData[3]) {
    speed = 8.0f;
    Unit::weapon = new WeaponRapidFire();
}
