<<<<<<< Updated upstream
#pragma once
#include <algorithm>
#include <memory>
#include <vector>
#include "SDL2/SDL.h"
#include "Vector2D.hpp"
#include "Pickup.hpp"
#include "Health.hpp"
#include "Coin.hpp"
#include "Ammo.hpp"
#include "UpgradeHealth.hpp"
#include "UpgradeAmmo.hpp"
#include "UpgradeWeaponSpeed.hpp"
class UnitEnemy;



class Level
{
public:
	static bool isBlockAtPos(int x, int y);
	
	static void setupAllEnemiesAndPickups(SDL_Renderer* renderer, Vector2D& posStart, Vector2D& posFinish, 
		std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies, std::vector<std::shared_ptr<Pickup>>& listPickups);


	static const char* levelData;

	static const int levelWidth;
	static const size_t levelSize;


	static const char symbolWall = 'X';
	//static const char symbolEmpty = ' ';

	static const char symbolHealth = 'H';
	static const char symbolCoin = 'C';
	static const char symbolAmmo = 'A';

	static const char symbolUpgradeHealth = 'h';
	static const char symbolUpgradeAmmo = 'a';
	static const char symbolUpgradeWeaponSpeed = 'w';

	static const char symbolStart = 'S';
	static const char symbolFinish = 'F';

	static const char symbolEnemySmall = '0';
	static const char symbolEnemyMedium = '1';
	static const char symbolEnemyLarge = '2';
=======
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
#include "UpgradeHealth.hpp"
#include "UpgradeAmmo.hpp"
#include "UpgradeWeaponSpeed.hpp"
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


	static const char* levelData;

	static const int levelWidth;
	static const size_t levelSize;


	static const char symbolWall = 'X';
	//static const char symbolEmpty = ' ';

	static const char symbolHealth = 'H';
	static const char symbolCoin = 'C';
	static const char symbolAmmo = 'A';

	static const char symbolUpgradeHealth = 'h';
	static const char symbolUpgradeAmmo = 'a';
	static const char symbolUpgradeWeaponSpeed = 'w';

	static const char symbolStart = 'S';
	static const char symbolFinish = 'F';

	static const char symbolEnemySmall = '0';
	static const char symbolEnemyMedium = '1';
	static const char symbolEnemyLarge = '2';
>>>>>>> Stashed changes
};