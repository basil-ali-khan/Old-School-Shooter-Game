#include "UnitEnemyMinor.hpp"


UnitEnemyMinor::UnitEnemyMinor(SDL_Renderer* renderer, Vector2D setPos, int type) :  UnitEnemy(renderer, setPos, type == 0 ? "UnitEnemyMinor1.bmp" : (type == 1 ? "UnitEnemyMinor2.bmp" : "UnitEnemyTankSplit.bmp"), type == 1 ? 1 : 2, type == 1 ? 6 : 2, false, Weapon(type == 0 ? 1 : 2, type == 1 ? 1 : 2, 20, type == 2 ? "Orb Blue Small.bmp" : "Orb Purple.bmp")) {

}

void UnitEnemyMinor::addUnitEnemyToList(SDL_Renderer* renderer, Vector2D setPos, int type, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    listUnitEnemies.push_back(std::make_shared<UnitEnemyMinor>(renderer, setPos, type));
}