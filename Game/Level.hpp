#pragma once
#include <algorithm>
#include <memory>
#include <vector>
// #include "SDL2/SDL.h"
#include "Vector2D.hpp"
#include "Pickup.hpp"
#include "Health.hpp"
#include "Coin.hpp"
#include "Ammo.hpp"
#ifdef __has_include
    // Check for the existence of the SDL2/SDL.h header file
    #if __has_include("SDL2/SDL.h")
        #include "SDL2/SDL.h"
        #include "SDL2_mixer/SDL_mixer.h"
    #else
        // If the header is not found, include the alternative headers
        #include <SDL.h>
        #include <SDL_image.h>
        #include <SDL_mixer.h>
    #endif
#endif
class UnitEnemy;



class Level
{
public:
	static bool isBlockAtPos(int x, int y);
	
	static void setupAllEnemiesAndPickups(SDL_Renderer* renderer, Vector2D& posStart, Vector2D& posFinish, 
		std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies, std::vector<std::shared_ptr<Pickup>>& listPickups);

	static void incrementArea();
	static void incrementKillCount();

	static const char* levelData;
	static int area;
	static int killCount;
	static int areaKillThreshold[5];

	static const int levelWidth;
	static const size_t levelSize;


	static const char symbolXWall = 'X';
	static const char symbolYWall = 'Y';
	static const char symbolZWall = 'Z';
	static const char symbolJWall = 'J';
	static const char symbolKWall = 'K';
	//static const char symbolEmpty = ' ';

	static const char symbolDoorOne = 'L';
	static const char symbolDoorTwo = 'M';
	static const char symbolDoorThree = 'N';
	static const char symbolDoorFour = 'O';
	static const char symbolDoorFive = 'P';

	static const char symbolHealth = 'H';
	static const char symbolCoin = 'C';
	static const char symbolAmmo = 'A';

	static const char symbolStart = 'S';
	static const char symbolFinish = 'F';

	static const char symbolEnemyOne = '0';
	static const char symbolEnemyTwo = '1';
	static const char symbolEnemyThree = '2';
	static const char symbolEnemyFour = '3';
	static const char symbolEnemyFive = '4';
};