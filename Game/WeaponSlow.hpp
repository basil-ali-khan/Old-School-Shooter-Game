#pragma once

#include "Weapon.hpp"

class WeaponSlow : public Weapon {
public:
    WeaponSlow();
    WeaponSlow(int setAmmo, int roundsPerSecond);    
};