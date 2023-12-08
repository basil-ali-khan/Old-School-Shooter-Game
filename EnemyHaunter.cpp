#include "EnemyHaunter.hpp"
#include "Game.hpp"

EnemyHaunter::EnemyHaunter(SDL_Renderer* renderer, Vector2D setPos) :  UnitEnemy(renderer, setPos, "EnemyHaunterAsleep.bmp", 6, 2, false, Weapon(-1, 8)) {

}

void EnemyHaunter::addUnitEnemyToList(SDL_Renderer* renderer, Vector2D setPos, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    listUnitEnemies.push_back(std::make_shared<EnemyHaunter>(renderer, setPos));
}

void EnemyHaunter::update(float dT, SDL_Renderer* renderer, Game& game, std::unique_ptr<UnitPlayer>& unitPlayer, 
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

