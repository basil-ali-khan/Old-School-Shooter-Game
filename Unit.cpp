#include "Unit.h"



Unit::Unit(SDL_Renderer* renderer, Vector2D setPos, std::string filenameForTexture) :
	Sprite(renderer, setPos, filenameForTexture, 0.5f/2) {

}