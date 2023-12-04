#pragma once
#include <vector>
#include <memory>
#include "SDL2_mixer/SDL_mixer.h"
// #include "SoundLoader.hpp"
#include "Projectile.hpp"
#include "Timer.hpp"



class Weapon
{
public:
	Weapon(int setAmmo, int roundsPerSecond);
	void update(float dT);
	void shootProjectile(SDL_Renderer* renderer, Vector2D start, Vector2D directionNormal, 
		std::vector<std::shared_ptr<Projectile>>& listProjectiles, bool setShotFromPlayer, 
		float angleSoundDeg = 0.0f, float distanceSound = 1.0f);
	bool isAmmoFull();
	void addAmmo(int amount);
	std::string computeAmmoString();
	void upgradeAmmoMax();
	void upgradeWeaponSpeed();


private:
	Timer cooldownTimer;

	static bool soundLoaded;
	static Mix_Chunk* mix_ChunkWeaponShoot;

	int roundsPerSecond;

	int ammo;
	int ammoMax = 30;
};