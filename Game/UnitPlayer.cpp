#include "UnitPlayer.hpp"



UnitPlayer::UnitPlayer(SDL_Renderer* renderer, Vector2D setPos) :
	Unit(renderer, setPos, "", 50, Weapon(8, 1, 20, "Orb Green.bmp")), angle(0.0f), speedMove(7.0f), speedTurn(2.0f), hitTimer(0.2f)  {
}



void UnitPlayer::shootProjectile(SDL_Renderer* renderer, std::vector<std::shared_ptr<Projectile>>& listProjectiles) {
    weapon.shootProjectile(renderer, pos, Vector2D(angle), listProjectiles, true);
}



void UnitPlayer::update(float dT) {
    Unit::update(dT);
    hitTimer.countDown(dT);


    //Create a vector called add that starts of as (0,0).
    Vector2D add;

    //If moving along the forward direction (froward or backward) then add that to add.
    if (directionForward != 0.0f)
        add += Vector2D(angle) * (float)copysign(1, directionForward);

    //If moving along the right direction (right or left) then add that to add.
    if (directionRight != 0.0f)
        add += Vector2D(angle).getNegativeReciprocal() * (float)copysign(1, directionRight);

    //If moving in both directions then the magnitude would be greater than 1.
    //Therefore normalize it to ensure that the magnitude is 1;
    add.normalize();

    //Because add is currently just the direction of movement, multiply it by the distance to move in this frame,
    //so that it's the total amount to move in this frame.
    add *= speedMove * dT;

    //Check if it needs to move in the x direction.  If so then check if the new x position, plus an amount of spacing 
    //(to keep from moving too close to the wall) is within a wall or not and update the position as required.
    const float spacing = 0.35f;
    if (add.x != 0.0f && Level::isBlockAtPos((int)(pos.x + add.x + copysign(spacing, add.x)), (int)(pos.y)) == false)
        pos.x += add.x;

    //Do the same for the y direction.
    if (add.y != 0.0f && Level::isBlockAtPos((int)(pos.x), (int)(pos.y + add.y + copysign(spacing, add.y))) == false)
        pos.y += add.y;


    //Update the angle that unit player is facing.
    angle += amountTurn * speedTurn;

    //Ensure that angle is between 0 and 2PI.
    if (angle > 2.0f * MathAddon::PI)
        angle -= 2.0f * MathAddon::PI;
    else if (angle < 0.0f)
        angle += 2.0f * MathAddon::PI;


    //Reset the variables for movement.
    directionForward = 0;
    directionRight = 0;
    amountTurn = 0.0f;
}



void UnitPlayer::setDirectionForward(int setDirectionForward) {
    directionForward = setDirectionForward;
}


void UnitPlayer::setDirectionRight(int setDirectionRight) {
    directionRight = setDirectionRight;
}


void UnitPlayer::setAmountTurn(float setAmountTurn) {
    amountTurn = setAmountTurn;
}



float UnitPlayer::getAngle() {
    return angle;
}



std::string UnitPlayer::getHealthString() {
    if (healthCurrent == healthMax)
        return "Max";
    else
        return std::to_string(healthCurrent);
}


bool UnitPlayer::isHealthFull() {
    return (healthCurrent == healthMax);
}


void UnitPlayer::addHealth(int amount) {
    if (amount > 0) {
        healthCurrent += amount;
        if (healthCurrent > healthMax)
            healthCurrent = healthMax;
    }
}

void UnitPlayer::removeHealth(int damage) {
    Unit::removeHealth(damage);
    
    if (damage > 0)
        hitTimer.resetToMax();
}



void UnitPlayer::addCoin() {
    countCoins++;
}


int UnitPlayer::getCountCoins() {
    return countCoins;
}


void UnitPlayer::addAmmo() {
    weapon.enterHighAmmoState();  // Activate high ammo state
}


std::string UnitPlayer::computeAmmoString() {
    return weapon.computeAmmoString();
}


bool UnitPlayer::wasRecentlyHit() {
    return !hitTimer.timeSIsZero();
}