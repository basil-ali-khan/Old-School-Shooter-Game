#pragma once

#include "UnitEnemy.hpp"

class E3 : public UnitEnemy {
private:
    static const std::string filenameForTexture;
    static const int healthMax;
    static const Weapon weapon;
    static const bool hasChanceToDropPickup;
    // const float speed = 2;
public:
    E3(SDL_Renderer* renderer, Vector2D setPos);
};