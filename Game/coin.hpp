#pragma once
#include "Pickup.hpp"



class Coin : public Pickup
{
public:
	Coin(SDL_Renderer* renderer, Vector2D setPos);
	bool addPickupToPlayer(std::unique_ptr<UnitPlayer>& unitPlayer);
};