<<<<<<< Updated upstream
#include "Ammo.hpp"
#include "UnitPlayer.hpp"



Ammo::Ammo(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Battery.bmp", "Ammo.ogg", true) {

}



bool Ammo::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr && unitPlayer->isAmmoFull() == false) {
		unitPlayer->addAmmo(10);
		return true;
	}

	return false;
=======
#include "Ammo.hpp"
#include "UnitPlayer.hpp"



Ammo::Ammo(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Battery.bmp", "Ammo.ogg", true) {

}



bool Ammo::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr && unitPlayer->isAmmoFull() == false) {
		unitPlayer->addAmmo(10);
		return true;
	}

	return false;
>>>>>>> Stashed changes
}