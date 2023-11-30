#include "Level.h"
#include "UnitEnemy.h"


const char* Level::levelData{
    "XXXXXXXXXX"
    "X     X0 X"
    "X  S  X  X"
    "X        X"
    "XXXXXXXXXX"


};

const int Level::levelWidth = 10;
const size_t Level::levelSize = strlen(levelData);



bool Level::isBlockAtPos(int x, int y) {
    int index = x + y * levelWidth;
    if (index > -1 && index < levelSize)
        return (levelData[index] == symbolWall);

    return false;
}



void Level::setupAllEnemies(SDL_Renderer* renderer, Vector2D& posStart, Vector2D& posFinish, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) 
    {

    for (int index = 0; index < levelSize; index++) {
        //The current position in the level in Vector2D form.
        Vector2D pos(
            (float)(index % levelWidth) + 0.5f,
            (float)(index / levelWidth) + 0.5f);

        //Check if any of the following symbols are found and modify the input positions and lists as required.
        switch (levelData[index]) {
        case symbolStart:
            posStart = pos;
            break;
        case symbolFinish:
            posFinish = pos;
            break;

        case symbolEnemySmall:
            UnitEnemy::addUnitEnemyToListUsingTemplate(renderer, pos, 0, listUnitEnemies);
            break;
        // case symbolEnemyMedium:
        //     UnitEnemy::addUnitEnemyToListUsingTemplate(renderer, pos, 1, listUnitEnemies);
        //     break;
        // case symbolEnemyLarge:
        //     UnitEnemy::addUnitEnemyToListUsingTemplate(renderer, pos, 2, listUnitEnemies);
        //     break;

        // case symbolHealth:
        //     listPickups.push_back(std::make_shared<Health>(renderer, pos));
        //     break;
        // case symbolCoin:
        //     listPickups.push_back(std::make_shared<Coin>(renderer, pos));
        //     break;
        // case symbolAmmo:
        //     listPickups.push_back(std::make_shared<Ammo>(renderer, pos));
        //     break;

        // case symbolUpgradeHealth:
        //     listPickups.push_back(std::make_shared<UpgradeHealth>(renderer, pos));
        //     break;
        // case symbolUpgradeAmmo:
        //     listPickups.push_back(std::make_shared<UpgradeAmmo>(renderer, pos));
        //     break;
        // case symbolUpgradeWeaponSpeed:
        //     listPickups.push_back(std::make_shared<UpgradeWeaponSpeed>(renderer, pos));
        //     break;
        }
    }
}

// void Level::setupStart(SDL_Renderer* renderer, Vector2D& posStart) {
//     for (int index = 0; index < levelSize; index++) {
//         //The current position in the level in Vector2D form.
//         Vector2D pos(
//             (float)(index % levelWidth) + 0.5f,
//             (float)(index / levelWidth) + 0.5f);

//         //Check if any of the following symbols are found and modify the input positions and lists as required.
//         switch (levelData[index]) {
//         case symbolStart:
//             posStart = pos;
//             break;
//         }
//     }
// }