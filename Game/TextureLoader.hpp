#pragma once
#include <string>
#include <unordered_map>
// #include "SDL2/SDL.h"
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


class TextureLoader
{
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string filename);
	static void deallocateTextures();


private:
	static std::unordered_map<std::string, SDL_Texture*> umapTexturesLoaded;
};