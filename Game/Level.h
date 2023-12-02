#pragma once
#include <algorithm>
#include <memory>
#include <vector>
#include "SDL.h"
#include "Vector2D.h"
// #include "UnitEnemy.h"
class UnitEnemy;


class Level
{
public:
	static bool isBlockAtPos(int x, int y);
	
	static void setupAllEnemies(SDL_Renderer* renderer, Vector2D& posStart, Vector2D& posFinish, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);

	static const char* levelData;

	static const int levelWidth;
	static const size_t levelSize;


	static const char symbolWall = 'X';
	static const char symbolEmpty = ' ';

	static const char symbolStart = 'S';
	static const char symbolFinish = 'F';

	static const char symbolEnemySmall = '0';

};