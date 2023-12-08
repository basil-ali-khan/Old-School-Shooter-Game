#pragma once
#include "Unit.hpp"
#include "UnitPlayer.hpp"
#include "MathAddon.hpp"
class Game;


class UnitEnemy : public Unit
{
protected:
	
	std::string filenameForTexture;
	int healthMax;
	float speed;
	Timer justHurtTimer;
	Timer playerBecameVisibleTimer;

public:
	UnitEnemy(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture, int setHealthMax, float setSpeed, bool setHasChanceToDropPickup, Weapon setWeapon);
	
	
	// static void addUnitEnemyToListUsingTemplate(SDL_Renderer* renderer, Vector2D setPos, int templateID,std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);
	
	virtual void update(float dT, SDL_Renderer* renderer, Game& game, std::unique_ptr<UnitPlayer>& unitPlayer, std::vector<std::shared_ptr<Projectile>>& listProjectiles);
	
	bool checkIfUnitPlayerVisible(Game& game, std::unique_ptr<UnitPlayer>& unitPlayer);
	
	void removeHealth(int amount);
	
	bool getHasChanceToDropPickup();

private:
	bool hasChanceToDropPickup;
	
};