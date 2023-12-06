<<<<<<< Updated upstream
#include "UpgradeWeaponSpeed.hpp"
#include "UnitPlayer.hpp"



UpgradeWeaponSpeed::UpgradeWeaponSpeed(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Upgrade Weapon Speed 10.bmp", "Upgrade.ogg", false) {

}



bool UpgradeWeaponSpeed::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr && unitPlayer->buyUpgradeWeaponSpeed())
		return true;

	return false;
=======
#include "UpgradeWeaponSpeed.hpp"
#include "UnitPlayer.hpp"



UpgradeWeaponSpeed::UpgradeWeaponSpeed(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Upgrade Weapon Speed 10.bmp", "Upgrade.ogg", false) {

}



bool UpgradeWeaponSpeed::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr && unitPlayer->buyUpgradeWeaponSpeed())
		return true;

	return false;
>>>>>>> Stashed changes
}