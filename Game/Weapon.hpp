#pragma once
#include <vector>
#include <memory>
// #include "SDL2_mixer/SDL_mixer.h"
// #include "SoundLoader.hpp"
#include "Projectile.hpp"
#include "Timer.hpp"
#ifdef __has_include
    // Check for the existence of the SDL2/SDL.h header file
    #if __has_include("SDL2/SDL.h")
        #include "SDL2/SDL.h"
        #include "SDL2_mixer/SDL_mixer.h"
    #else
        // If the header is not found, include the alternative headers
        #include <SDL.h>
        #include <SDL_image.h>
        #include <SDL_mixer.h>
    #endif
#endif


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

	void enterHighAmmoState();  // New method to activate high ammo state
    void updateHighAmmo(float dT);  // New method to update high ammo state


private:
	Timer cooldownTimer;

	static bool soundLoaded;
	static Mix_Chunk* mix_ChunkWeaponShoot;

	int roundsPerSecond;

	int ammo;
	int ammoMax = 30;

	bool isHighAmmo = false;  // New variable to track high ammo state
    Timer highAmmoTimer = Timer(5.0f);  // New timer to track high ammo state
};