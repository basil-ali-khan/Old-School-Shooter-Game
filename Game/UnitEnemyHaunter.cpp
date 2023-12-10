#include "UnitEnemyHaunter.hpp"
#include "Game.hpp"

UnitEnemyHaunter::UnitEnemyHaunter(SDL_Renderer* renderer, Vector2D setPos) :  UnitEnemy(renderer, setPos, "UnitEnemyHaunterAsleep.bmp", 10, 8, true, Weapon(-1, 8, 2, 20, "Orb Purple.bmp")) {

}

void UnitEnemyHaunter::addUnitEnemyToList(SDL_Renderer* renderer, Vector2D setPos, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    listUnitEnemies.push_back(std::make_shared<UnitEnemyHaunter>(renderer, setPos));
}

void UnitEnemyHaunter::update(float dT, SDL_Renderer* renderer, Game& game, std::unique_ptr<UnitPlayer>& unitPlayer, 
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
		&& unitPlayerVisible && unitPlayer != nullptr && awake) {
		Vector2D directionPlayer(unitPlayer->getPos() - pos);
		Vector2D directionNormal(Vector2D(directionPlayer).normalize());

		float angleSoundDeg = MathAddon::angleRadToDeg(directionNormal.angleBetween(Vector2D(unitPlayer->getAngle())));

		weapon.shootProjectile(renderer, pos, directionNormal, listProjectiles, false, angleSoundDeg, directionPlayer.magnitude());
	}

    if (unitPlayer != nullptr && !awake && std::get<0>(game.raycast(getPos(), (unitPlayer->getPos() - getPos()).normalize(), true)) >0) {
        Vector2D directionToPlayer = (unitPlayer->getPos() - getPos()).normalize();
        float distanceToPlayer = directionToPlayer.magnitude();
        if ((unitPlayer->getPos() - getPos()).magnitude() < 7) {
            awake = true;
			setTexture("UnitEnemyHaunterAwake.bmp");
			Vector2D teleportVector = directionToPlayer.normalize() * -1.3f; 
            setPos(unitPlayer->getPos() + teleportVector);
        }
    }

	if (awake && std::get<0>(game.raycast(getPos(), (unitPlayer->getPos() - getPos()).normalize(), true)) > 1.3) {
		// Move towards player
		Vector2D directionToPlayer = (unitPlayer->getPos() - getPos()).normalize();
		Vector2D newPos = getPos() + directionToPlayer * speed * dT;
		if (!Level::isBlockAtPos(static_cast<int>(newPos.x), static_cast<int>(newPos.y))) {
			setPos(newPos);
		}
	}



}

