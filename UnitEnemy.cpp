#include "UnitEnemy.hpp"
#include "Game.hpp"
#include <iostream>


// const std::vector<UnitEnemy::TemplateData> UnitEnemy::listTemplateData = {
// 	{"EnemyMinor1.bmp", 2, Weapon(-1, 1), false },
// 	{"EnemyMinor2.bmp", 4, Weapon(-1, 4), true },
// 	{"EnemyHaunterAwake.bmp", 6, Weapon(-1, 8), true }
// };


UnitEnemy::UnitEnemy(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture, int setHealthMax, float setSpeed, bool setHasChanceToDropPickup, Weapon setWeapon) :
	Unit(renderer, setPos, filenameForTexture, setHealthMax, setWeapon),
	justHurtTimer(0.25f), playerBecameVisibleTimer(2.0f),
	hasChanceToDropPickup(hasChanceToDropPickup), speed(setSpeed)
	{

}


// void UnitEnemy::addUnitEnemyToListUsingTemplate(SDL_Renderer* renderer, Vector2D setPos, int templateID,
//     std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    
//     if (templateID > -1 && templateID < listTemplateData.size()) {
// 		if (templateID == 0) {
// 			listUnitEnemies.push_back(std::make_shared<E1>(renderer, setPos));
// 		}
// 		else if (templateID == 1) {
// 			listUnitEnemies.push_back(std::make_shared<E2>(renderer, setPos));
// 		}
// 		else if (templateID == 2) {
// 			listUnitEnemies.push_back(std::make_shared<E3>(renderer, setPos));
// 		}
//     }
// }


void UnitEnemy::update(float dT, SDL_Renderer* renderer, Game& game, std::unique_ptr<UnitPlayer>& unitPlayer, 
	std::vector<std::shared_ptr<Projectile>>& listProjectiles) {

	Unit::update(dT);

	justHurtTimer.countDown(dT);
	drawRed = (justHurtTimer.timeSIsZero() == false);


	//Check and handle player visibility.
	bool unitPlayerVisible = checkIfUnitPlayerVisible(game, unitPlayer);

	if (unitPlayerVisible)
		playerBecameVisibleTimer.countUp(dT);
	else
		playerBecameVisibleTimer.countDown(dT);


	//If unit player has been visible for long enough then shoot it.
	if (playerBecameVisibleTimer.timeSIsGreaterThanOrEqualTo(0.5f)
		&& unitPlayerVisible && unitPlayer != nullptr) {
		Vector2D directionPlayer(unitPlayer->getPos() - pos);
		Vector2D directionNormal(Vector2D(directionPlayer).normalize());

		float angleSoundDeg = MathAddon::angleRadToDeg(directionNormal.angleBetween(Vector2D(unitPlayer->getAngle())));

		weapon.shootProjectile(renderer, pos, directionNormal, listProjectiles, false, angleSoundDeg, directionPlayer.magnitude());
	}

	// Check if player is in sight
    if (std::get<0>(game.raycast(getPos(), (unitPlayer->getPos() - getPos()).normalize(), true)) > 1.75) {
        // Move towards player
        Vector2D directionToPlayer = (unitPlayer->getPos() - getPos()).normalize();
        Vector2D newPos = getPos() + directionToPlayer * speed * dT;
        if (!Level::isBlockAtPos(static_cast<int>(newPos.x), static_cast<int>(newPos.y))) {
			setPos(newPos);
        }
    }
}



bool UnitEnemy::checkIfUnitPlayerVisible(Game& game, std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr) {
		Vector2D normal((unitPlayer->getPos() - pos).normalize());

		float distance = std::get<0>(game.raycast(pos, normal, true));
		if (distance > 0.0f)
			return true;
	}

	return false;
}



void UnitEnemy::removeHealth(int damage) {
	Unit::removeHealth(damage);

	if (damage > 0)
		justHurtTimer.resetToMax();
}



bool UnitEnemy::getHasChanceToDropPickup() {
	return hasChanceToDropPickup;
}