<<<<<<< Updated upstream
#include "Coin.hpp"
#include "UnitPlayer.hpp"



Coin::Coin(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Coin.bmp", "Coin.ogg", true) {

}



bool Coin::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr) {
		unitPlayer->addCoin();
		return true;
	}

	return false;
=======
#include "Coin.hpp"
#include "UnitPlayer.hpp"



Coin::Coin(SDL_Renderer* renderer, Vector2D setPos) :
	Pickup(renderer, setPos, "Coin.bmp", "Coin.ogg", true) {

}



bool Coin::addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer) {
	if (unitPlayer != nullptr) {
		unitPlayer->addCoin();
		return true;
	}

	return false;
>>>>>>> Stashed changes
}