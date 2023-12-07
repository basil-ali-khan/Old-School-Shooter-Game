#pragma once
// #include "SDL2/SDL.h"
#include "Sprite.hpp"
#include "Weapon.hpp"
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


class Unit : public Sprite
{
public:
	Unit(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture, int setHealthMax);
	void update(float dT);
	void draw(SDL_Renderer* renderer);
	bool isAlive();
	void removeHealth(int amount);


protected:
	int healthMax;
	int healthCurrent = healthMax;

	Weapon* weapon;
};