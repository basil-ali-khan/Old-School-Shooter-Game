<<<<<<< Updated upstream
#pragma once
#include "Pickup.hpp"



class UpgradeWeaponSpeed : public Pickup
{
public:
	UpgradeWeaponSpeed(SDL_Renderer* renderer, Vector2D setPos);
	bool addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer);
=======
#pragma once
#include "Pickup.hpp"



class UpgradeWeaponSpeed : public Pickup
{
public:
	UpgradeWeaponSpeed(SDL_Renderer* renderer, Vector2D setPos);
	bool addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer);
>>>>>>> Stashed changes
};