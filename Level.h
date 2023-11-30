#pragma once
#include <algorithm>
#include <memory>
#include <vector>
// #include "SDL2/SDL.h"
#include "Vector2D.h"

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



class Level
{
public:
	static bool isBlockAtPos(int x, int y);
	
	static void setupStartandFinish(SDL_Renderer* renderer, Vector2D& posStart, Vector2D& posFinish); 

	static const char* levelData;

	static const int levelWidth;
	static const size_t levelSize;


	static const char symbolWall = 'X';
	static const char symbolEmpty = ' ';

	static const char symbolStart = 'S';
	static const char symbolFinish = 'F';

};