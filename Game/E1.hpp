#pragma once

#include "UnitEnemy.hpp"

class E1 : public UnitEnemy {
private:
    static const std::string filenameForTexture;
    static const int healthMax;
    static const Weapon weapon;
    static const bool hasChanceToDropPickup;
    // const float speed = 1.0f;
public:
    E1(SDL_Renderer* renderer, Vector2D setPos);
};