#pragma once
#include "Unit.h"
#include "Vector2D.h"
#include "MathAddon.h"
#include "Level.h"





class UnitPlayer : public Unit
{
public:
	UnitPlayer(SDL_Renderer* renderer, Vector2D setPos);
	void update(float dT);
	void setDirectionForward(int setDirectionForward);
	void setDirectionRight(int setDirectionRight);
	void setAmountTurn(float setDirectionTurn);
	float getAngle();


private:
	int directionForward = 0, directionRight = 0;
	float amountTurn = 0.0f;

	float angle;
	const float speedMove, speedTurn;

};