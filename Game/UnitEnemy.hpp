#pragma once
#include "Unit.hpp"
#include "UnitPlayer.hpp"
#include "MathAddon.hpp"
class Game;



class UnitEnemy : public Unit
{
private:
	struct TemplateData {
		std::string filenameForTexture;
		int healthMax;
		Weapon weapon;
		bool hasChanceToDropPickup;
	};
	static const std::vector<TemplateData> listTemplateData;


public:
	UnitEnemy(SDL_Renderer* renderer, Vector2D setPos, TemplateData unitEnemyTemplateData, float setSpeed);
	static void addUnitEnemyToListUsingTemplate(SDL_Renderer* renderer, Vector2D setPos, int templateID,
		std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);
	void update(float dT, SDL_Renderer* renderer, Game& game, std::unique_ptr<UnitPlayer>& unitPlayer, 
		std::vector<std::shared_ptr<Projectile>>& listProjectiles);
	bool checkIfUnitPlayerVisible(Game& game, std::unique_ptr<UnitPlayer>& unitPlayer);
	void removeHealth(int amount);
	bool getHasChanceToDropPickup();


private:
	float speed;
	Timer justHurtTimer;
	Timer playerBecameVisibleTimer;

	bool hasChanceToDropPickup;
};