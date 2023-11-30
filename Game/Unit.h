#pragma once
#include "SDL.h"
#include "Sprite.h"
#include "Weapon.h"



class Unit : public Sprite
{
public:
	Unit(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture, int setHealthMax, Weapon setWeapon);
	bool isAlive();
	void update(float dT);
protected:
	int healthMax;
	int healthCurrent = healthMax;

	Weapon weapon;
};