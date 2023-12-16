#include "SoundLoader.hpp"
#include <iostream>

std::unordered_map<std::string, Mix_Chunk*> SoundLoader::umapSoundsLoaded;
std::unordered_map<std::string, Mix_Music*> SoundLoader::umapMusicLoaded;



Mix_Chunk* SoundLoader::loadSound(std::string filename) {
    if (filename != "") {
        auto found = umapSoundsLoaded.find(filename);

        if (found != umapSoundsLoaded.end()) {
            //The sound was already loaded so return it.
            return found->second;
        }
        else {
            //Setup the relative filepath to the sounds folder using the input filename.
            std::string filepath = "Data/Sounds/" + filename;

            //Try to create a mix_Chunk using the filepath.
            Mix_Chunk* mix_Chunk = Mix_LoadWAV(filepath.c_str());
            if (mix_Chunk != nullptr) {

                //Add the mix_Chunk to the map of loaded mix_Chunks to keep track of it and for clean-up purposes.
                umapSoundsLoaded[filename] = mix_Chunk;

                return mix_Chunk;
            }
        }
    }

    return nullptr;
}



Mix_Music* SoundLoader::loadMusic(std::string filename) {
    if (!filename.empty()) {
        auto found = umapMusicLoaded.find(filename);
        if (found != umapMusicLoaded.end()) {
            // Music already loaded
            return found->second;
        } else {
            // Load new music
            std::string filepath = "Data/Sounds/" + filename;
            Mix_Music* music = Mix_LoadMUS(filepath.c_str());
            if (music != nullptr) {
                umapMusicLoaded[filename] = music;
                return music;
            } else {
                // Handle error: could not load music
                std::cerr << "Could not load music: " << Mix_GetError() << std::endl;
            }
        }
    }
    return nullptr;
}


void SoundLoader::deallocateSounds() {
	//Stop the sounds first
    Mix_HaltChannel(-1);

    //Destroy all the sounds
    while (umapSoundsLoaded.empty() == false) {
        auto it = umapSoundsLoaded.begin();
        if (it->second != nullptr)
            Mix_FreeChunk(it->second);

        umapSoundsLoaded.erase(it);
    }
}


void SoundLoader::deallocateMusic() {
    for (auto& music : umapMusicLoaded) {
        if (music.second != nullptr) {
            Mix_FreeMusic(music.second);
        }
    }
    umapMusicLoaded.clear();
}