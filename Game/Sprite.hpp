#pragma once
#include <string>
#include <memory>
// #include "SDL2/SDL.h"
#include "TextureLoader.hpp"
#include "Vector2D.hpp"
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
class UnitPlayer;
class Game;



class Sprite
{
public:
	Sprite(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture, float setOverlapRadius = 0.5f, float setDrawScale = 1.0f);
	void draw(SDL_Renderer* renderer, int worldWidth, int worldHeight, std::unique_ptr<UnitPlayer>& unitPlayer, 
		float fovRad, float listDepthDraw[]);
	bool checkOverlap(Sprite* other);
	Vector2D getPos();
	void setPos(Vector2D setPos);


protected:
	Vector2D pos;
	bool drawRed = false;


private:
	SDL_Texture* texture = nullptr;
	float overlapRadius, drawScale;
};