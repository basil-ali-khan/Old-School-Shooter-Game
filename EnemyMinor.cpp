#include "EnemyMinor.hpp"
#include <iostream> 

EnemyMinor::EnemyMinor(SDL_Renderer* renderer, Vector2D setPos, int type) :  UnitEnemy(renderer, setPos, type == 0 ? "EnemyMinor1.bmp" : "EnemyMinor2.bmp", 2 - type*1, 2*type + 2, false, Weapon(-1, 1 + type)) {

}

void EnemyMinor::addUnitEnemyToList(SDL_Renderer* renderer, Vector2D setPos, int type, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    listUnitEnemies.push_back(std::make_shared<EnemyMinor>(renderer, setPos, type));
}

