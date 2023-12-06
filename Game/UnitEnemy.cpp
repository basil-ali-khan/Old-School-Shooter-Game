<<<<<<< Updated upstream
#include "UnitEnemy.hpp"
#include "Game.hpp"


const std::vector<UnitEnemy::TemplateData> UnitEnemy::listTemplateData = {
	{"Alien Small.bmp", 1, Weapon(-1, 1), false },
	{"Alien Medium.bmp", 3, Weapon(15, 4), true },
	{"Alien Large.bmp", 6, Weapon(30, 8), true }
};




UnitEnemy::UnitEnemy(SDL_Renderer* renderer, Vector2D setPos, TemplateData unitEnemyTemplateData, float setSpeed) :
	Unit(renderer, setPos,
		unitEnemyTemplateData.filenameForTexture,
		unitEnemyTemplateData.healthMax,
		unitEnemyTemplateData.weapon),
	justHurtTimer(0.25f), playerBecameVisibleTimer(2.0f),
	hasChanceToDropPickup(unitEnemyTemplateData.hasChanceToDropPickup),
	speed(setSpeed) {

}



void UnitEnemy::addUnitEnemyToListUsingTemplate(SDL_Renderer* renderer, Vector2D setPos, int templateID,
	std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
	if (templateID > -1 && templateID < listTemplateData.size()) {
		listUnitEnemies.push_back(std::make_shared<UnitEnemy>(renderer, setPos, listTemplateData[templateID], 2));
	}
}



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
    if (game.raycast(getPos(), (unitPlayer->getPos() - getPos()).normalize(), true).first > 0) {
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

		float distance = game.raycast(pos, normal, true).first;
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
=======
#include "UnitEnemy.hpp"
#include "Game.hpp"
#include "E1.hpp"
#include "E2.hpp"
#include "E3.hpp"
#include "E4.hpp"
#include "E5.hpp"



const std::vector<UnitEnemy::TemplateData> UnitEnemy::listTemplateData = {
	{"Alien Small.bmp", 1, Weapon(-1, 1), false },
	{"Alien Medium.bmp", 3, Weapon(15, 4), true },
	{"Alien Large.bmp", 6, Weapon(30, 8), true }
};




// UnitEnemy::UnitEnemy(SDL_Renderer* renderer, Vector2D setPos, TemplateData unitEnemyTemplateData, float setSpeed) :
// 	Unit(renderer, setPos,
// 		unitEnemyTemplateData.filenameForTexture,
// 		unitEnemyTemplateData.healthMax,
// 		unitEnemyTemplateData.weapon),
// 	justHurtTimer(0.25f), playerBecameVisibleTimer(2.0f),
// 	hasChanceToDropPickup(unitEnemyTemplateData.hasChanceToDropPickup),
// 	speed(setSpeed) {

// }

// UnitEnemy::UnitEnemy(SDL_Renderer* renderer, Vector2D setPos, TemplateData unitEnemyTemplateData) :
// 	Unit(renderer, setPos,
// 		unitEnemyTemplateData.filenameForTexture,
// 		unitEnemyTemplateData.healthMax,
// 		unitEnemyTemplateData.weapon),
// 	justHurtTimer(0.25f), playerBecameVisibleTimer(2.0f),
// 	hasChanceToDropPickup(unitEnemyTemplateData.hasChanceToDropPickup),
// 	speed(setSpeed) {

// }
UnitEnemy::UnitEnemy(SDL_Renderer* renderer, Vector2D setPos, TemplateData unitEnemyTemplateData) :
	Unit(renderer, setPos, unitEnemyTemplateData.filenameForTexture, unitEnemyTemplateData.healthMax),
	justHurtTimer(0.25f), playerBecameVisibleTimer(2.0f),
	hasChanceToDropPickup(unitEnemyTemplateData.hasChanceToDropPickup)
	{

}



// void UnitEnemy::addUnitEnemyToListUsingTemplate(SDL_Renderer* renderer, Vector2D setPos, int templateID,
// 	std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
// 	int eNumber = rand() % 2;
// 	if (templateID > -1 && templateID < listTemplateData.size()) {
// 		if (eNumber == 0) {
// 		templateID = 0;
// 		UnitEnemy E1(renderer, setPos, listTemplateData[0]);
// 		listUnitEnemies.push_back(std::make_shared<UnitEnemy>(E1));
// 		}
// 		else if (eNumber == 1) {
// 		templateID = 1;
// 		UnitEnemy E2(renderer, setPos, listTemplateData[1]);
// 		listUnitEnemies.push_back(std::make_shared<UnitEnemy>(E2));
// 		}
// 		// else if (eNumber == 2) {
// 		// templateID = 2;
// 		// UnitEnemy E3(renderer, setPos, listTemplateData[2]);
// 		// listUnitEnemies.push_back(std::make_shared<UnitEnemy>(E3));
		
// 		// }
// 	}
// }
void UnitEnemy::addUnitEnemyToListUsingTemplate(SDL_Renderer* renderer, Vector2D setPos, int templateID,
    std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    int eNumber = rand() % 2;
    if (templateID > -1 && templateID < listTemplateData.size()) {
        if (eNumber == 0) {
            listUnitEnemies.push_back(std::make_shared<E1>(renderer, setPos));
        } else if (eNumber == 1) {
            listUnitEnemies.push_back(std::make_shared<E2>(renderer, setPos));
        }
        // Add similar conditions for other enemy types (E3, E4, E5) if needed
		else if (eNumber == 2) {
			listUnitEnemies.push_back(std::make_shared<E3>(renderer, setPos));
		}
		else if (eNumber == 3) {
			listUnitEnemies.push_back(std::make_shared<E4>(renderer, setPos));
		}
		else if (eNumber == 4) {
			listUnitEnemies.push_back(std::make_shared<E5>(renderer, setPos));
		}
    }
}




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

		weapon->shootProjectile(renderer, pos, directionNormal, listProjectiles, false, angleSoundDeg, directionPlayer.magnitude());
	}

	// Check if player is in sight
    if (game.raycast(getPos(), (unitPlayer->getPos() - getPos()).normalize(), true).first > 0) {
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

		float distance = game.raycast(pos, normal, true).first;
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
>>>>>>> Stashed changes
}