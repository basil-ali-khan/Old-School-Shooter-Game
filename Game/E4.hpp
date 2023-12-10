#pragma once

#include "UnitEnemy.hpp"

class E4 : public UnitEnemy {
private:
    static const std::string filenameForTexture;
    static const int healthMax;
    static const Weapon weapon;
    static const bool hasChanceToDropPickup;
    // const float speed = 2;
public:
    E4(SDL_Renderer* renderer, Vector2D setPos);
};