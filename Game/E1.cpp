#include "E1.hpp"
#include "UnitEnemy.hpp"
#include "WeaponSlow.hpp"

E1::E1(SDL_Renderer* renderer, Vector2D setPos) :  UnitEnemy(renderer, setPos, UnitEnemy::listTemplateData[0]) {
    speed = 2.0f;
    Unit::weapon = new WeaponSlow();
}

