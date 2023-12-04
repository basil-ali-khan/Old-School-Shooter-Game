#pragma once
#include "Pickup.hpp"



class Ammo : public Pickup
{
public:
	Ammo(SDL_Renderer* renderer, Vector2D setPos);
	bool addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer);
};