#include "Weapon.hpp"


bool Weapon::soundLoaded = false;
Mix_Chunk* Weapon::mix_ChunkWeaponShoot = nullptr;




Weapon::Weapon(int setRoundsPerSecond, int setDamage, float setProjectileSpeed, std::string setFilenameProjectile) :
roundsPerSecond(setRoundsPerSecond), cooldownTimer(setRoundsPerSecond > 0 ? (setRoundsPerSecond == 10 ? (1.0f/0.333f) : (1.0f / setRoundsPerSecond)) : (1.0f / 2)),
damage(setDamage), projectileSpeed(setProjectileSpeed), filenameProjectile(setFilenameProjectile),
isHighAmmo(false), highAmmoTimer(5.0f) {
	if (soundLoaded == false) {
		mix_ChunkWeaponShoot = SoundLoader::loadSound("Energy Orb.ogg");
		soundLoaded = (mix_ChunkWeaponShoot != nullptr);
	}
}


void Weapon::enterHighAmmoState() {
    isHighAmmo = true;
    highAmmoTimer.resetToMax();
}

void Weapon::updateHighAmmo(float dT) {
    if (isHighAmmo) {
        highAmmoTimer.countDown(dT);
        if (highAmmoTimer.timeSIsZero()) {
            isHighAmmo = false;
			// Reset firing speed
			cooldownTimer = Timer(roundsPerSecond > 0 ? (1.0f / roundsPerSecond) : (1.0f / 2));
        }
    }
}


void Weapon::update(float dT) {
	// Triple the speed when high ammo
	cooldownTimer.countDown(dT * (isHighAmmo ? 3.0f : 1.0f));
    updateHighAmmo(dT);
}


void Weapon::shootProjectile(SDL_Renderer* renderer, Vector2D start, Vector2D directionNormal, 
	std::vector<std::shared_ptr<Projectile>>& listProjectiles, bool setShotFromPlayer, 
	float angleSoundDeg, float distanceSound) {
	//Ensure the weapon is ready to shoot.
	if (cooldownTimer.timeSIsZero()) {
		//The projectile will move from the start position in the direction of directionNormal.
		//Add the projectile to the list.
		listProjectiles.push_back(std::make_unique<Projectile>(renderer, start, directionNormal, setShotFromPlayer, projectileSpeed, damage, filenameProjectile));

		// Play sound.
		if (mix_ChunkWeaponShoot != nullptr) {
			int channelSelected = Mix_PlayChannel(-1, mix_ChunkWeaponShoot, 0);
			//If it wasn't shot from the player then adjust it's volume based on it's position and angle relative to the player.
			if (setShotFromPlayer == false && channelSelected > -1) {
				float fDistanceSound = sqrt(distanceSound / 50.0f);
				if (fDistanceSound < 0.0f)
					fDistanceSound = 0.0f;
				if (fDistanceSound > 0.7f)
					fDistanceSound = 0.7f;

				Mix_SetPosition(channelSelected, (int)angleSoundDeg, (int)(fDistanceSound * 255));
			}
		}

		cooldownTimer.resetToMax();
	}

}


std::string Weapon::computeAmmoString() {
	if (isHighAmmo) {
        return "Max";
	}
    return "Low";
}