#include "Level.hpp"
#include "UnitEnemy.hpp"
#include "EnemyMinor.hpp"
#include "EnemyHaunter.hpp"
#include <iostream>


const char* Level::levelData{
    "XYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXY"
    "XJ                                  JJJJJJJJJJJJJJJY"
    "YJ                                  J   K         JX"
    "XJ                                  J   K         JY"
    "YJ                                  J   K         JX"
    "XJ         JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ      JY"
    "YJ         J                               J      JX"
    "XJ         J        JJJJJJ JJJJJJJJJ J JJJ J      JY"
    "YJJJJJJJJJJJ        J    J J       J J JJJ JJJ JJJJX"
    "XJ         J        JJJJJJ JJJJJJJJJ J            JY"
    "YJJJJJJ             J                JJJJJJJJJJJJJJX"
    "XJ       JJJJJJ     J  JJJJJJJJJJJJJJJJJJJJJJJJJJJJY"
    "YJ       J             JZZZZZZZZZZZZZZZZZZZZZZZZZZZX"
    "XJ       J  JJJJJJ     JZ      Z                  ZY"
    "YJJJJJJJJJ             JZ      ZZZZZZZZZZZZZZ     ZX"
    "X            JJJJJ  JJJJZ             Z           ZY"
    "YJJJJJJJJJJJJJ F JJJJZZZZZZZZZZZ      Z     Z     ZX"
    "XZZZZZZZZZZZZZOOZZZZZ         Z            Z     ZY"
    "YZ                 Z           ZZZZZZZZZZZZZZ     ZX"
    "XZ               ZZZZZZZZZ     Z                  ZY"
    "YZZZZZZZZZZZZZ     Z   Z    ZZZZZZZ               ZY"
    "XYYYYYYYYYYYYZ     Z                       ZZZZZZZZY"
    "Y 1  1  1   YZ                                    ZY"
    "Y  YYYYY  1 YZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ  Y"
    "Y 1H1H 1    YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNNY"
    "Y H Y 1H 1   1   Y 1H Y 1 H 1   Y  1    1       1Y1Y"
    "Y 1 YYYYYYYYYY 1 Y  1 Y  1H Y 1 Y1  YYYYY 1 HY  Y  Y"
    "Y H1  H 1 H 1HH  Y 1  Y 1   Y 1 Y  1 H  1  HHY  Y  Y"
    "YYYYYYYYYYYYYY YYYYH YY 1 H Y   YYYYYYYYYYYYYY     Y"
    "XXYXYXYXYXYXYY 1   H 1   1H Y  1 H 1 H             Y"
    "YY0 H  11  1 M  A  1   YYYYYY1 H YYYYYYYYYYYYYYYYYSY"
    "XX Y00 1  11 M   1  1 A   1 HH 1 H 1 H             Y"
    "YY X  Y 0    XYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYX"
    "XX Y  X              0          0     0          0 Y"
    "YY X  Y  YXYX 0  0        0  X     0       0   X   X"
    "XX    0     X      H   0     Y H0      0       Y   Y"
    "YY  0    XY YXYXXY           XXYXYXYXYXY 0   0 X000X"
    "XX  YXYXYXYA0    0   XYXYXYXYY             0 H Y   Y"
    "YY       H     0      0      X  0HA0   0     A X   X"
    "XXXXXXXXXXXXXXXXXXX    A  0  Y       XYXYXYXYXYX   Y"
    "X         X 0     X  0     H X  0  0 X 0  0      0 X"
    "X   0          0 HXX H  0 A          H         0   Y"
    "X         X 0     XYA0AXYXYXYXXYXYXYXYXYXYXYXYXYXYXY"
    "X  0    0 XXXXXXXXXX              HH  A            Y"
    "X                 XYXYXYXYXYXYXYXYLLY      0  0    X"
    "X          0      X              X  X    0     0   Y"
    "X   0             X              X  X      0       X"
    "X       A     0   XXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXY"
    "X                 X0                X     A A     XX"
    "XXXXXXXXX XXXXXXXXX    0      A     X   0  H  0   XY"
    "YXXXXXX X0X       XXX    XX      0  X    0   0    XX"
    "X     XXX XXXXXXXXX      XX         X             XY"
    "X                        XX      XX X   XX   XX   XX"
    "X  A                             XX 0         0   XY"
    "X     XXXXXXXXXXXXX       A       X   H   0       XX"
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXY"


};

const int Level::levelWidth = 52;
const size_t Level::levelSize = strlen(levelData);

int Level::area = 1;
int Level::killCount = 0;
int Level::areaKillThreshold[5] = { 20, 72, 117, 30, 40 };

/*
20 LVL 1
52 LVL 2
45 LVL 3
*/

bool Level::isBlockAtPos(int x, int y) {
    int index = x + y * levelWidth;
    if (index > -1 && index < levelSize)
        return (levelData[index] == symbolXWall or levelData[index] == symbolYWall or levelData[index] == symbolZWall or levelData[index] == symbolJWall or levelData[index] == symbolKWall or (area == 1 and levelData[index] == symbolDoorOne) or (area == 2 and levelData[index] == symbolDoorTwo) or (area == 3 and levelData[index] == symbolDoorThree) or (area == 4 and levelData[index] == symbolDoorFour));

    return false;
}



void Level::setupAllEnemiesAndPickups(SDL_Renderer* renderer, Vector2D& posStart, Vector2D& posFinish, 
    std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies, std::vector<std::shared_ptr<Pickup>>& listPickups) {
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

        case symbolEnemyOne:
            EnemyMinor::addUnitEnemyToList(renderer, pos, 0, listUnitEnemies);
            break;
        case symbolEnemyTwo:
            EnemyMinor::addUnitEnemyToList(renderer, pos, 1, listUnitEnemies);
            break;
        case symbolEnemyThree:
            EnemyHaunter::addUnitEnemyToList(renderer, pos, listUnitEnemies);
            break;
        // case symbolEnemyFour:
        //     UnitEnemy::addUnitEnemyToListUsingTemplate(renderer, pos, 3, listUnitEnemies);
        //     break;
        // case symbolEnemyFive:
        //     UnitEnemy::addUnitEnemyToListUsingTemplate(renderer, pos, 4, listUnitEnemies);
        //     break;

        case symbolHealth:
            listPickups.push_back(std::make_shared<Health>(renderer, pos));
            break;
        case symbolCoin:
            listPickups.push_back(std::make_shared<Coin>(renderer, pos));
            break;
        case symbolAmmo:
            listPickups.push_back(std::make_shared<Ammo>(renderer, pos));
            break;

        case symbolUpgradeHealth:
            listPickups.push_back(std::make_shared<UpgradeHealth>(renderer, pos));
            break;
        case symbolUpgradeAmmo:
            listPickups.push_back(std::make_shared<UpgradeAmmo>(renderer, pos));
            break;
        case symbolUpgradeWeaponSpeed:
            listPickups.push_back(std::make_shared<UpgradeWeaponSpeed>(renderer, pos));
            break;
        }
    }
}

void Level::incrementArea() {
    area++;
}

void Level::incrementKillCount() {
    killCount++;
}