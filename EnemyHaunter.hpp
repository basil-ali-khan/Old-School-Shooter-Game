#pragma once

#include "UnitEnemy.hpp"


class EnemyHaunter : public UnitEnemy {
private:
public:
    EnemyHaunter(SDL_Renderer* renderer, Vector2D setPos);

    static void addUnitEnemyToList(SDL_Renderer* renderer, Vector2D setPos, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);

    void update(float dT, SDL_Renderer* renderer, Game& game, std::unique_ptr<UnitPlayer>& unitPlayer, 
	std::vector<std::shared_ptr<Projectile>>& listProjectiles);
};