#include "E3.hpp"
#include "UnitEnemy.hpp"
#include "WeaponFast.hpp"

E3::E3(SDL_Renderer* renderer, Vector2D setPos) :  UnitEnemy(renderer, setPos, UnitEnemy::listTemplateData[2]) {
    speed = 6.0f;
    Unit::weapon = new WeaponFast();
}
