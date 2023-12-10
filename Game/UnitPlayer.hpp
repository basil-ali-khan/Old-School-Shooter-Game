#pragma once
#include "Unit.hpp"
#include "Vector2D.hpp"
#include "MathAddon.hpp"
#include "Weapon.hpp"
#include "Timer.hpp"



class UnitPlayer : public Unit
{
public:
	UnitPlayer(SDL_Renderer* renderer, Vector2D setPos);
	void update(float dT);
	void shootProjectile(SDL_Renderer* renderer, std::vector<std::shared_ptr<Projectile>>& listProjectiles);
	void setDirectionForward(int setDirectionForward);
	void setDirectionRight(int setDirectionRight);
	void setAmountTurn(float setDirectionTurn);
	float getAngle();
	std::string getHealthString();
	bool isHealthFull();
	void addHealth(int amount);
	void removeHealth(int amount);
	void addCoin();
	int getCountCoins();
	// bool isAmmoFull();
	void addAmmo();
	std::string computeAmmoString();

	bool wasRecentlyHit();
	Timer hitTimer;

private:
	int directionForward = 0, directionRight = 0;
	float amountTurn = 0.0f;

	float angle;
	const float speedMove, speedTurn;

	int countCoins = 0;
};