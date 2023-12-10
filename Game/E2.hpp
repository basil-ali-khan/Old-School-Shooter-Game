#pragma once

#include "UnitEnemy.hpp"

class E2 : public UnitEnemy {
private:
    static const std::string filenameForTexture;
    static const int healthMax;
    static const Weapon weapon;
    static const bool hasChanceToDropPickup;
    // const float speed = 2;
public:
    E2(SDL_Renderer* renderer, Vector2D setPos);
};