<<<<<<< Updated upstream
#include "UpgradeHealth.hpp"
#include "UnitPlayer.hpp"



UpgradeHealth::UpgradeHealth(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Upgrade Heart 10.bmp", "Upgrade.ogg", false) {

}



bool UpgradeHealth::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr && unitPlayer->buyUpgradeHealthMax())
		return true;

	return false;
=======
#include "UpgradeHealth.hpp"
#include "UnitPlayer.hpp"



UpgradeHealth::UpgradeHealth(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Upgrade Heart 10.bmp", "Upgrade.ogg", false) {

}



bool UpgradeHealth::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr && unitPlayer->buyUpgradeHealthMax())
		return true;

	return false;
>>>>>>> Stashed changes
}