#pragma once
#include "Pickup.hpp"



class UpgradeHealth : public Pickup
{
public:
	UpgradeHealth(SDL_Renderer* renderer, Vector2D setPos);
	bool addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer);
};