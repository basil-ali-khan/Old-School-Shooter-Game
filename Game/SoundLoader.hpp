#pragma once
#include <string>
#include <unordered_map>
// #include "SDL2_mixer/SDL_mixer.h"

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

class SoundLoader
{
public:
	static Mix_Chunk* loadSound(std::string filename);
	static void deallocateSounds();


private:
	static std::unordered_map<std::string, Mix_Chunk*> umapSoundsLoaded;
};