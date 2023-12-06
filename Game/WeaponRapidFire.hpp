#pragma once

#include "Weapon.hpp"

class WeaponRapidFire : public Weapon {
public:
    WeaponRapidFire();
    WeaponRapidFire(int setAmmo, int roundsPerSecond);

};