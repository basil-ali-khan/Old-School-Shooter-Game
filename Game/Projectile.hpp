<<<<<<< Updated upstream
#pragma once
#include "SDL2/SDL.h"
#include "Sprite.hpp"
#include "TextureLoader.hpp"
#include "Level.hpp"
class UnitPlayer;
class UnitEnemy;



class Projectile : public Sprite
{
public:
	Projectile(SDL_Renderer* renderer, Vector2D setPos, Vector2D setDirectionNormal, bool setShotFromPlayer);
	void update(float dT, std::unique_ptr<UnitPlayer>& unitPlayer, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);
	bool getCollisionOccurred();


private:
	void checkCollisions(std::unique_ptr<UnitPlayer>& unitPlayer, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);


	Vector2D directionNormal;

	const float speed = 20.0f;

	const int damage = 1;

	const bool shotFromPlayer;

	bool collisionOccurred = false;
=======
#pragma once
// #include "SDL2/SDL.h"
#include "Sprite.hpp"
#include "TextureLoader.hpp"
#include "Level.hpp"
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
class UnitEnemy;



class Projectile : public Sprite
{
public:
	Projectile(SDL_Renderer* renderer, Vector2D setPos, Vector2D setDirectionNormal, bool setShotFromPlayer);
	void update(float dT, std::unique_ptr<UnitPlayer>& unitPlayer, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);
	bool getCollisionOccurred();


private:
	void checkCollisions(std::unique_ptr<UnitPlayer>& unitPlayer, std::vector<std::shared_ptr<UnitEnemy>>& listUnitEnemies);


	Vector2D directionNormal;

	const float speed = 20.0f;

	const int damage = 1;

	const bool shotFromPlayer;

	bool collisionOccurred = false;
>>>>>>> Stashed changes
};