#include "Projectile.hpp"
#include "UnitEnemy.hpp"
#include "Game.hpp"



Projectile::Projectile(SDL_Renderer* renderer, Vector2D setPos, Vector2D setDirectionNormal, bool setShotFromPlayer, int setSpeed, int setDamage, std::string filename) :
    Sprite(renderer, setPos, filename, 0.125f / 2, filename == "Orb Blue.bmp" ? 0.35f : 0.125f),
    directionNormal(setDirectionNormal), shotFromPlayer(setShotFromPlayer), speed(setSpeed), damage(setDamage) {

}



void Projectile::update(float dT, std::unique_ptr<UnitPlayer>& unitPlayer, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    if (collisionOccurred == false) {
        //Move the projectile forward.
        pos += directionNormal * speed * dT;

        if (Level::isBlockAtPos((int)pos.x, (int)pos.y))
            //If the projectiles center point is in a wall then it collided with a wall.
            collisionOccurred = true;
        else
            checkCollisions(unitPlayer, listUnitEnemies);
    }
}



bool Projectile::getCollisionOccurred() {
    return collisionOccurred;
}



void Projectile::checkCollisions(std::unique_ptr<UnitPlayer>& unitPlayer, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies) {
    //Check for a collision with any of the units.
    if (collisionOccurred == false) {
        if (shotFromPlayer == false) {
            //Check if this overlaps unit player or not.
            if (unitPlayer != nullptr && unitPlayer->checkOverlap(this)) {
                unitPlayer->removeHealth(damage);
                collisionOccurred = true;
            }
        }
        else {
            //Check if this overlaps any of the enemy units or not.
            for (int count = 0; count < listUnitEnemies.size() && collisionOccurred == false; count++) {
                auto& unitEnemySelected = listUnitEnemies[count];
                if (unitEnemySelected != nullptr && unitEnemySelected->checkOverlap(this)) {
                    unitEnemySelected->removeHealth(damage);
                    collisionOccurred = true;
                }
            }
        }
    }
}