#include "E2.hpp"
#include "UnitEnemy.hpp"
#include "WeaponMedium.hpp"


E2::E2(SDL_Renderer* renderer, Vector2D setPos) :  UnitEnemy(renderer, setPos, UnitEnemy::listTemplateData[1]) {
    speed = 4.0f;
    Unit::weapon = new WeaponMedium();
}
