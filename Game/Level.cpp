#include "Level.hpp"
#include "UnitEnemy.hpp"
#include "UnitEnemyMinor.hpp"
#include "UnitEnemyHaunter.hpp"
#include "UnitEnemyTank.hpp"
#include <iostream>


// const char* Level::levelData{
//     "XYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXY"
//     "XJ                                  JJJJJJJJJJJJJJJY"
//     "YJ                                  J   K         JX"
//     "XJ                                  J   K         JY"
//     "YJ                                  J   K         JX"
//     "XJ         JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ      JY"
//     "YJ         J                               J      JX"
//     "XJ         J        JJJJJJ JJJJJJJJJ J JJJ J      JY"
//     "YJJJJJJJJJJJ        J    J J       J J JJJ JJJ JJJJX"
//     "XJ         J        JJJJJJ JJJJJJJJJ J            JY"
//     "YJJJJJJ             J                JJJJJJJJJJJJJJX"
//     "XJ       JJJJJJ     J  JJJJJJJJJJJJJJJJJJJJJJJJJJJJY"
//     "YJ       J             JZZZZZZZZZZZZZZZZZZZZZZZZZZZX"
//     "XJ       J  JJJJJJ     JZ      Z  2               ZY"
//     "YJJJJJJJJJ             JZ  2   ZZZZZZZZZZZZZZA1H AZX"
//     "X            JJJJJ  JJJJZ         0   Z       1 1 ZY"
//     "YJJJJJJJJJJJJJ F JJJJZZZZZZZZZZZ  0   Z A  Z   1  ZX"
//     "XZZZZZZZZZZZZZOOZZZZZ1 0   0  Z   0  A     Z    1 ZY"
//     "YZ2        1 1     Z111  0  0 ZZZZZZZZZZZZZZ      ZX"
//     "XZ          1 1    ZZZZZZZ   0Z 0  0   0   A0 0   ZY"
//     "YZZZZZZZZZZZZZ HH  Z  1Z    ZZZZZZZ  0   0  A1    ZY"
//     "XYYYYYYYYYYYYZ AA  Z 11  A   0    A  0 H   ZZZZZZZZY"
//     "YY1  1  1   YZ      1          0   0   H          ZY"
//     "YYAYYYYYA 1 YZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ  Y"
//     "YY1H1H 1  A YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNNY"
//     "YYH Y 1H 1 A 1CCCY 1H Y 1 H 1   Y  1CCC 1  CCCC 1Y1Y"
//     "YY1 YYYYYYYYYYA1 Y  1 Y  1H Y 1 Y1  YYYYY 1 HY  Y  Y"
//     "YYH1  H 1 H 1HH  Y 1A Y 1   Y 1 Y  1 H  1  HHY  Y  Y"
//     "YYYYYYYYYYYYYY YYYYH YY 1 H YCCCYYYYYYYYYYYYYY     Y"
//     "XXYXYXYXYXYXYYA1 A H 1CCC1H Y  1 H 1 H   A  CCCCCCCY"
//     "YY0 H  11  1 M  A  1   YYYYYY1 H YYYYYYYYYYYYYYYYYSY"
//     "XX Y00 1  11 M   1  1 A   1 HH 1 H 1 H   A         Y"
//     "YYCX  Y 0    XYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYX"
//     "XXCY  X CCC     CCC  0          0     0          0 Y"
//     "YYCX  Y  YXYX 0  0   CCC  0  X     0       0   X   X"
//     "XX    0 CCCCX      H   0     Y H0      0       Y   Y"
//     "YY  0    XY YXYXXY           XXYXYXYXYXY 0   0 X000X"
//     "XX  YXYXYXYA0    0   XYXYXYXYY    CCC      0 H Y   Y"
//     "YY       H     0      0      X  0HA0   0     A X   X"
//     "XXXXXXXXXXXXXXXXXXX    A  0  Y  CC   XYXYXYXYXYX   Y"
//     "X         X 0     X  0     H X  0  0 X 0  0      0 X"
//     "XC  0  C       0 HXX H  0 A    CCC   H         0   Y"
//     "X         X 0     XYA0AXYXYXYXXYXYXYXYXYXYXYXYXYXYXY"
//     "X  0 C  0 XXXXXXXXXX   CCC        HH  A            Y"
//     "X                 XYXYXYXYXYXYXYXYLLY      0  0    X"
//     "X  C   C   0      X              X  X    0 CCC 0   Y"
//     "X  C0             X              X  X      0       X"
//     "X  C    A     0   XXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXY"
//     "X  C              X0                X     A A     XX"
//     "XXXXXXXXX XXXXXXXXX    0      A     X   0  H  0   XY"
//     "YXXXXXX X0X       XXX C  XX  C   0  X    0   0    XX"
//     "X  S  XXX XXXXXXXXX   C  XX  C      X             XY"
//     "X                     C  XX  C   XX X   XX   XX   XX"
//     "X  A                         C   XX 0         0   XY"
//     "X     XXXXXXXXXXXXX       A       X   H   0       XX"
//     "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXY"


// };

const char* Level::levelData{
    "XYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXY"
    "XJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJY"
    "YJ        0         A             0 J   K11    1  JX"
    "XJ 2  3                 HHH     0HHHJF3 K111 2   1JY"
    "YJ      0   0       A             0 J   K11    1  JX"
    "XJ    2    JJJJJJJJJJJJJS  JJJJJJJJJJJJJJJJJ 1    JY"
    "YJ 0    0  J  0      0                     J      JX"
    "XJ    0    J      0 JJ  JJ JJJ   JJJ J JJJ J      JY"
    "YJJJJJJJJJJJ 0      J11111 J0 AHA 0J J JJJ JJJ JJJJX"
    "XJHA0      J    0   JJ  JJ JJJ   JJJ J  0         JY"
    "YJJJJJJ      0      J    0 0     0   JJJJJJJJJ JJJJX"
    "XJ1 2   1JJJJJJ  0  J  JJJJJJJJJJJJJJJ   0        JJ"
    "YJ 1HH1  J   0  0  H   J  2     0      A    HHH  0JX"
    "XJ 1 1 1 J0 JJJJJJ   0 J 1 3 1 1  0      0     0  JJ"
    "YJJJJJJJJJ   H         J  1     1      A    0     JJ"
    "XH2   0          H  JJJJ 2 1 1    0        A      JJ"
    "YJJJJJJJJJJJJJOOOJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"
    "Y            J   J      ZZZZZZZZZZZZZZZZZZZZZZZZZZZX"
    "X            J   J      Z 1 1  Z  2               ZY"
    "Y            J   J      Z1 2 1 ZZZZZZZZZZZZZZA1H AZX"
    "X            J   J      Z 1 1     0   Z       1 1 ZY"
    "Y            J   J  ZZZZZZZZZZZZ  0   Z A  Z   1  ZX"
    "XZZZZZZZZZZZZZOOOZZZZ1 0   0  Z   0  A     Z    1 ZY"
    "YZ2         1      Z111  0  0 ZZZZZZZZZZZZZZ      ZX"
    "XZ         111     ZZZZZZZ   0Z 0  0   0   A0 0   ZY"
    "YZZZZZZZZZZZZZ HH  Z   Z    ZZZZZZZ  0   0  A1    ZY"
    "X            Z AA  Z     A   0    A  0 H   ZZZZZZZZY"
    "Y            Z                 0   0   H          ZY"
    "Y            ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZNNZ"
    "XYYYYYYYYYYYY                                   Z  Z"
    "YY1  1  1   Y                                   Z  Z"
    "YYAYYYYYA11 Y                                   Z  Z"
    "YY1H1H 111A YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNNY"
    "YYH Y 1H 1 A 1CCCY 1H Y 1 H 1   Y  1CCC 1  CCCC 1 1Y"
    "YY1 YYYYYYYYYYA1 Y  1 Y  1H Y 1 Y1  YYYYY 1 HY  Y  Y"
    "YYH1  H 1 H 1HH  Y 1A Y 1   Y 1 Y  1 H  1  HHY  Y1 Y"
    "YYYYYYYYYYYYYY YYYYH YY 1 H YCCCYYYYYYYYYYYYYY 1   Y"
    "X       Y    YA1 A H 1CCC1H Y  1 H 1 H   A  CCCCCCCY"
    "Y       Y    M  A  1   YYYYYY1 H YYYYYYYYYYYYYYYYY Y"
    "X       Y    M   1  1 A   1 HH 1 H 1 H   A         Y"
    "YYYYYYYYY  YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY" 
    "YYYYYYYYY      Y                                   Y" 
    "YYYYYYYYYYYYY  Y                                   Y" 
    "XYXYXYXYXYXYY  Y                                   Y"
    "YY0H   11111 M Y                                   Y"
    "XX Y00 11111 M Y                                   Y"
    "YYCX  Y 0    XYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYXYX"
    "XXCY  X CCC     CCC  0          0     0  0       0 Y"
    "YYCX  Y  YXYX 0  0   CCC  0  X     0       0   X   X"
    "XX    0 CCCCX      H   0     Y H0      0       Y   Y"
    "YY  0    XY YXYXXY 0         XXYXYXYXYXY 0   0 X000X"
    "XX  YXYXYXYA0    0   XYXYXYXYY    CCC      0 H Y   Y"
    "YY0      H     0      0      X  0HA0   0     A X   X"
    "XXXYXYXYXYXYXYXYXYX    A  0  Y  CC   XYXYXYXYXYX   Y"
    "X                 Y  0     H X  0  0 X 0  0      0 X"
    "X                 XX H  0 A    CCC   H         0   Y"
    "X                 XYA0AXYXYXYXXYXYXYXYXYXYXYXYXYXYXY"
    "X                 XX   CCC        HH  A            Y"
    "X                 XYXYXYXYXYXYXYXYLLY      0  0    X"
    "X                 X              X  X    0 CCC 0   Y"
    "X                 X              X  X      0 0     X"
    "XXXXXXXXXXXXXXXXXXX              X  YYXYXYXYXYXYXYXY"
    "X         X 0     X              Y  X              X"
    "XC  0  C       0 HX              X  Y              Y"
    "X         X 0     X              Y  Y              Y"
    "X  0 C  0 XXXXXXXXX              X  X              Y"
    "X                 XYXYXYXYXYXYXYXYLLX              X"
    "X  C   C   0      X              X  X              Y"
    "X  C0             X              X  X              X"
    "X  C    A     0   XXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXY"
    "X  C              X0                X     A A     XX"
    "XXXXXXXXX XXXXXXXXX    0      A     X   0  H  0   XY"
    "YXXXXXX X0X       XXX C  XX  C   0  X    0   0    XX"
    "X     XXX XXXXXXXXX   C  XX  C      X             XY"
    "X                     C  XX  C    X X   XX   XX   XX"
    "X  A     CCCC                C    X 0         0   XY"
    "X     XXXXXXXXXXXXX       A       X   H   0       XX"
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXY"
};

const int Level::levelWidth = 52;
const size_t Level::levelSize = strlen(levelData);

int Level::area = 1;
int Level::killCount = 0;
// int Level::areaKillThreshold[5] = { 20, 72, 117, 30, 40 };
int Level::areaKillThreshold[5] = { 20, 80, 130, 172, 248};

/*
20 LVL 1
60 LVL 2
50 LVL 3
40 LVL 4
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
            UnitEnemyMinor::addUnitEnemyToList(renderer, pos, 0, listUnitEnemies);
            break;
        case symbolEnemyTwo:
            UnitEnemyMinor::addUnitEnemyToList(renderer, pos, 1, listUnitEnemies);
            break;
        case symbolEnemyThree:
            UnitEnemyHaunter::addUnitEnemyToList(renderer, pos, listUnitEnemies);
            break;
        case symbolEnemyFour:
            UnitEnemyTank::addUnitEnemyToList(renderer, pos, listUnitEnemies);
            break;
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