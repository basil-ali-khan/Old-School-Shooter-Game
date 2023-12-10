#pragma once

#include "UnitEnemy.hpp"


class UnitEnemyMinor : public UnitEnemy {
private:
public:
    UnitEnemyMinor(SDL_Renderer* renderer, Vector2D setPos, int type);

    static void addUnitEnemyToList(SDL_Renderer* renderer, Vector2D setPos, int type, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);
};