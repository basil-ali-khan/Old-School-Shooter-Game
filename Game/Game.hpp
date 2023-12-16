#pragma once
#include <vector>
#include <chrono>
#include <memory>
#include <vector>
#include <iostream>
// #include "SDL2/SDL.h"
// #include "SDL2_mixer/SDL_mixer.h"
#include "Sprite.hpp"
#include "TextureLoader.hpp"
#include "SoundLoader.hpp"
#include "UnitEnemy.hpp"
#include "Projectile.hpp"
#include "Level.hpp"
#include "Timer.hpp"
#include "Pickup.hpp"
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



class Game
{
private:
	enum class Mode {
		instructions,
		playing,
		victory,
		defeat
	} gameModeCurrent;


public:

	Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight);
	~Game();
	std::tuple<float, float, char> raycast(Vector2D posStart, Vector2D normal, bool findWallFPlayerT);


private:
	void processEvents(bool& running, SDL_Renderer* renderer, SDL_Window* window, int windowWidth, int windowHeight);
	void update(float dT, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, std::string framerate);
	void drawWorld(SDL_Renderer* renderer);

	void drawOverlayInstructions(SDL_Renderer* renderer);
	void drawOverlayPlaying(SDL_Renderer* renderer);
	void drawOverlayLevelIncrement(SDL_Renderer* renderer);
	void drawOverlayVictory(SDL_Renderer* renderer);
	void drawOverlayDefeat(SDL_Renderer* renderer);

	void drawWalls(SDL_Renderer* renderer);
	void addAllSpritesToDrawList(SDL_Renderer* renderer);
	void addSpriteToDrawList(std::shared_ptr<Sprite>& sprite);
	void sortAndDrawListSpritesToDraw(SDL_Renderer* renderer);
	void drawText(SDL_Renderer* renderer, int offsetX, int offsetY, int size, std::string textToDraw);
	void addRandomPickup(SDL_Renderer* renderer, Vector2D pos);
	void drawRedOverlay(SDL_Renderer* renderer);



	static const int worldWidth = 1920, worldHeight = 1080;
	SDL_Texture* textureScreen = nullptr,
		* textureHeart = nullptr, * textureAmmo = nullptr, * textureCoin = nullptr,
		* textureCrosshair = nullptr,
		* textureFont = nullptr,
		* texturePlayButton = nullptr; // for play button

	std::shared_ptr<Sprite> spriteFlag;

	float listDepthDraw[worldWidth] = {};
	std::vector<std::pair<float, std::weak_ptr<Sprite>>> listSpritesToDraw;


	int mouseDownStatus = 0;


	static const float fovRad;
	int levelIncrementOverlayTimer = 0;


	std::unique_ptr<UnitPlayer> unitPlayer = nullptr;

	std::vector<std::shared_ptr<UnitEnemy>> listUnitEnemies;
	std::vector<std::shared_ptr<Pickup>> listPickups;
	std::vector<std::shared_ptr<Projectile>> listProjectiles;

	std::vector<bool> listVisibleCells;

	int mouseXLast = 0;
	bool mouseXLastSet = false;

	int moveToNextLevelMessageTimer = 0;
	
	static Mix_Music* backgroundMusic;
};