#pragma once
#include "SDL2/SDL.h"
#include "Sprite.h"



class Unit : public Sprite
{
public:
	Unit(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture);
};