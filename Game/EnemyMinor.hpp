#pragma once

#include "UnitEnemy.hpp"


class EnemyMinor : public UnitEnemy {
private:
public:
    EnemyMinor(SDL_Renderer* renderer, Vector2D setPos, int type);

    static void addUnitEnemyToList(SDL_Renderer* renderer, Vector2D setPos, int type, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);


};