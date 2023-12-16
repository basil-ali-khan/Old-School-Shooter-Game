#include "Game.hpp"
#include "UnitEnemyMinor.hpp"
#include <iostream>

const float Game::fovRad = MathAddon::angleDegToRad(60.0f);
Mix_Music* Game::backgroundMusic = nullptr;

Game::Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) :
    gameModeCurrent(Mode::instructions) {
    //Run the game.
    if (window != nullptr && renderer != nullptr) {
        //Initialize a texture that will be used to draw the world.  It will be a scaled amount of the screen.
        textureScreen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, worldWidth, worldHeight);
        SDL_SetTextureBlendMode(textureScreen, SDL_BLENDMODE_BLEND);

        //Load some needed textures.
        textureFont = TextureLoader::loadTexture(renderer, "Font.bmp");
        textureCrosshair = TextureLoader::loadTexture(renderer, "Crosshair.bmp");
        //The following are for the in game overlay.
        textureHeart = TextureLoader::loadTexture(renderer, "Heart.bmp");
        textureAmmo = TextureLoader::loadTexture(renderer, "Battery.bmp");
        textureCoin = TextureLoader::loadTexture(renderer, "Coin.bmp");
        texturePlayButton = TextureLoader::loadTexture(renderer, "playbutton.bmp");

        //Load the level data.
        Vector2D posStart, posFinish;
        Level::setupAllEnemiesAndPickups(renderer, posStart, posFinish, listUnitEnemies, listPickups);
        unitPlayer = std::make_unique<UnitPlayer>(renderer, posStart);
        spriteFlag = std::make_shared<Sprite>(renderer, posFinish, "Flag.bmp");

        listVisibleCells.assign(Level::levelSize, false);

        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "SDL_mixer could not initialize. SDL_mixer Error: " << Mix_GetError() << std::endl;
        }

        // Load and play background music
        backgroundMusic = SoundLoader::loadMusic("Background.ogg");
        if (backgroundMusic != nullptr) {
            Mix_PlayMusic(backgroundMusic, -1); // -1 means looping the music
        }


        //Store the current times for the clock.
        auto time1 = std::chrono::system_clock::now();
        auto time2 = std::chrono::system_clock::now();

        //The amount of time for each frame (60 fps).
        const float dT = 1.0f / 60.0f;


        //Start the game loop and run until it's time to stop.
        bool running = true;
        while (running) {
            //Determine how much time has elapsed since the last frame.
            time2 = std::chrono::system_clock::now();
            std::chrono::duration<float> timeDelta = time2 - time1;
            float timeDeltaFloat = timeDelta.count();

            //If enough time has passed then do everything required to generate the next frame.
            if (timeDeltaFloat >= dT) {
                //Store the new time for the next frame.
                time1 = time2;

                //Process events.
                processEvents(running, renderer, window, windowWidth, windowHeight);

                //Update.  Only do so if the game mode is playing.
                if (gameModeCurrent == Mode::playing)
                    update(timeDeltaFloat, renderer);

                //Draw.
                std::string framerate = (timeDeltaFloat > 0.0f ? std::to_string((int)round(1.0f / timeDeltaFloat)) : "Inf");
                draw(renderer, framerate);
            }
        }
    }
}



Game::~Game() {
    //Clean up.
    if (textureScreen != nullptr) {
        SDL_DestroyTexture(textureScreen);
        textureScreen = nullptr;
    }
    TextureLoader::deallocateTextures();
    SoundLoader::deallocateSounds();

    if (texturePlayButton != nullptr) {
        SDL_DestroyTexture(texturePlayButton);
        texturePlayButton = nullptr;
    }

    // Stop and free the background music
    if (backgroundMusic != nullptr) {
        Mix_HaltMusic();
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }

    // Close the audio device
    Mix_CloseAudio();  
}



void Game::processEvents(bool& running, SDL_Renderer* renderer, SDL_Window* window, int windowWidth, int windowHeight) {
    bool mouseDownThisFrame = false;

    //Process events.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (gameModeCurrent == Mode::instructions) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Define the play button area
                SDL_Rect playButtonRect = {800, 750, 300, 92};
                // Mouse X: 555 Mouse Y: 687
                // Mouse X: 905 Mouse Y: 796
                if (mouseX >= 621 && mouseX <= 833 && mouseY >= 650 && mouseY <= 708) {
                    gameModeCurrent = Mode::playing;
                    SDL_SetRelativeMouseMode(SDL_TRUE); // Hide cursor when playing
                }
            }
            else {
                //Otherwise store the mouse event information.
                mouseDownThisFrame = (mouseDownStatus == 0);
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouseDownStatus = SDL_BUTTON_LEFT;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseDownStatus = SDL_BUTTON_RIGHT;
            }

            break;
        case SDL_MOUSEBUTTONUP:
            mouseDownStatus = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                //Quit the game.
            case SDL_SCANCODE_ESCAPE:
                running = false;
                break;
            }
            break;
        }
    }

    //Get the relative movement of the mouse.
    int mouseXOffset;
    SDL_GetRelativeMouseState(&mouseXOffset, NULL);

    if (unitPlayer != nullptr && gameModeCurrent == Mode::playing) {
        //A more responsive/faster way to check keypresses for the unit movement.
        const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
        //Make the unit move if needed.
        if (keyboardState[SDL_SCANCODE_A])
            unitPlayer->setDirectionRight(-1);
        if (keyboardState[SDL_SCANCODE_D])
            unitPlayer->setDirectionRight(1);
        if (keyboardState[SDL_SCANCODE_W])
            unitPlayer->setDirectionForward(1);
        if (keyboardState[SDL_SCANCODE_S])
            unitPlayer->setDirectionForward(-1);

        //Make the unit turn if needed.
        if (mouseXOffset != 0)
            unitPlayer->setAmountTurn((float)mouseXOffset / windowWidth);

        //Make the unit shoot if needed.
        if (mouseDownStatus == SDL_BUTTON_LEFT)
            unitPlayer->shootProjectile(renderer, listProjectiles);
    }
}



void Game::update(float dT, SDL_Renderer* renderer) {
    //Update.
    if (unitPlayer != nullptr) {
        unitPlayer->update(dT);
        if (unitPlayer->isAlive() == false)
            gameModeCurrent = Mode::defeat;
        else if (spriteFlag != nullptr && spriteFlag->checkOverlap(unitPlayer.get()))
            gameModeCurrent = Mode::victory;
    }

    //Update the enemy units.
    for (int count = 0; count < listUnitEnemies.size(); count++) {
        auto& unitEnemySelected = listUnitEnemies[count];
        if (unitEnemySelected != nullptr) {
            unitEnemySelected->update(dT, renderer, *this, unitPlayer, listProjectiles);
            if (unitEnemySelected->isAlive() == false) {
                if (unitEnemySelected->getHasChanceToDropPickup())
                    addRandomPickup(renderer, unitEnemySelected->getPos());

                // if EnemyTank, spawn 3 EnemyMinor units
                if (unitEnemySelected->getIsTank()) {
                    Vector2D pos = unitEnemySelected->getPos();
                    listUnitEnemies.push_back(std::make_shared<UnitEnemyMinor>(renderer, Vector2D(pos.x + 0.5f, pos.y + 0.5f), 2));
                    listUnitEnemies.push_back(std::make_shared<UnitEnemyMinor>(renderer, Vector2D(pos.x + 0.5f, pos.y - 0.5f), 2));
                    listUnitEnemies.push_back(std::make_shared<UnitEnemyMinor>(renderer, Vector2D(pos.x - 0.5f, pos.y + 0.5f), 2));
                }

                // if EnemyTank, don't increment kill count
                if (!unitEnemySelected->getIsTank()) {
                    Level::incrementKillCount();
                }

                listUnitEnemies.erase(listUnitEnemies.begin() + count);
                count--;
            }
        }
    }

    // Ensure we're not already at the last level
    if (Level::area < 5) {
        // if killCount reaches or exceeds area threshold, increment area
        if (Level::killCount >= Level::areaKillThreshold[Level::area-1]) {
            Level::incrementArea();
            levelIncrementOverlayTimer = 180;
            moveToNextLevelMessageTimer = 480; // Set timer for 5 seconds (assuming 60 FPS)
        }
    }
    
    // we're at the last level
    if (Level::area == 5) {
        // if killCount reaches or exceeds area threshold, increment area
        if (Level::killCount >= Level::areaKillThreshold[Level::area-1]) {
            Level::incrementArea();
        }
    }

    if (moveToNextLevelMessageTimer > 0) {
        moveToNextLevelMessageTimer--;
    }

    // Check if the current level is the last and all enemies are defeated
    if (Level::area == 5 && Level::killCount >= Level::areaKillThreshold[Level::area - 1]) {
        // Display the flag if not already displayed
        if (spriteFlag != nullptr && !spriteFlag->isVisible()) {
            spriteFlag->setVisible(true);  // Assuming you have a method to make the flag visible
        }
    }

    // Check for victory condition (player reaches the flag)
    if (spriteFlag != nullptr && spriteFlag->checkOverlap(unitPlayer.get()) && spriteFlag->isVisible()) {
        gameModeCurrent = Mode::victory;
        moveToNextLevelMessageTimer = 0; // Reset message timer
    }

    //Update the pickups.
    for (int count = 0; count < listPickups.size(); count++) {
        auto& pickupSelected = listPickups.at(count);
        if (pickupSelected != nullptr) {
            pickupSelected->update(unitPlayer);
            if (pickupSelected->getConsumed()) {
                listPickups.erase(listPickups.begin() + count);
                count--;
            }
        }
    }

    //Update the projectiles.
    for (int count = 0; count < listProjectiles.size(); count++) {
        auto& projectileSelected = listProjectiles.at(count);
        if (projectileSelected != nullptr) {
            projectileSelected->update(dT, unitPlayer, listUnitEnemies);
            if (projectileSelected->getCollisionOccurred()) {
                listProjectiles.erase(listProjectiles.begin() + count);
                count--;
            }
        }
    }
}



void Game::draw(SDL_Renderer* renderer, std::string framerate) {
    //Clear the screen.
    //Set the draw color to black (it will be the color of the ceiling)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    //Switch the render target to textureScreen and clear it.
    SDL_SetRenderTarget(renderer, textureScreen);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    //Draw the entire world.
    drawWorld(renderer);

    //Draw the overlays.
    switch (gameModeCurrent) {
    case Mode::instructions:
        drawOverlayInstructions(renderer);
        break;
    case Mode::playing:
        drawOverlayPlaying(renderer);
        if (levelIncrementOverlayTimer > 0) {
            levelIncrementOverlayTimer--;
            drawOverlayLevelIncrement(renderer);
        }
        break;
    case Mode::victory:
        drawOverlayVictory(renderer);
        break;
    case Mode::defeat:
        drawOverlayDefeat(renderer);
        break;
    }

    //Set the render target back to the window.
    SDL_SetRenderTarget(renderer, NULL);
    //Draw the texture.
    SDL_RenderCopy(renderer, textureScreen, NULL, NULL);

    // Draw red overlay if player was recently hit - make sure this is after all other rendering calls
    if (unitPlayer != nullptr && unitPlayer->wasRecentlyHit()) {
        drawRedOverlay(renderer);
    }

    //Send the image to the window.
    SDL_RenderPresent(renderer);
}



void Game::drawWorld(SDL_Renderer* renderer) {
    //Set the draw color to light gray (for the floor)
    SDL_SetRenderDrawColor(renderer, 75, 75, 75, 255);
    //Draw a rectangle that covers the bottom half of the screen.
    //Note that the +1 to the height is incase worldHeight / 2 has round off error.
    SDL_Rect rectFloor = { 0, worldHeight / 2, worldWidth, (worldHeight / 2 + 1) };
    SDL_RenderFillRect(renderer, &rectFloor);


    drawWalls(renderer);
    addAllSpritesToDrawList(renderer);
    //Draw a number on the screen for the number of sprites that need to be drawn.
    //drawText(renderer, 2, 14, 1, std::to_string(listSpritesToDraw.size()));
    sortAndDrawListSpritesToDraw(renderer);
}



void Game::drawOverlayInstructions(SDL_Renderer* renderer) {
    //Draw a transparent black overlay that covers the whole screen.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_Rect rectBackground{ 0,0, worldWidth, worldHeight };
    SDL_RenderFillRect(renderer, &rectBackground);

    //Draw the text.
    drawText(renderer, 450, 200, 8, "W, A, S, D:  Movement");
    drawText(renderer, 450, 320, 8, "Move Mouse:  Turn");
    drawText(renderer, 450, 440, 8, "Left Click:  Hold to Shoot");
    drawText(renderer, 450, 560, 8, "ESC:         Quit");
    // drawText(renderer, 72, 100, 1, "-Click to Start-");

    // Draw the play button
    if (texturePlayButton != nullptr) {
        SDL_Rect playButtonRect = {800, 750, 300, 92};
        SDL_RenderCopy(renderer, texturePlayButton, NULL, &playButtonRect);
    }
}


void Game::drawOverlayPlaying(SDL_Renderer* renderer) {
    if (unitPlayer != nullptr) {
        //Draw a transparent black overlay that covers a bit of the bottom left of the screen.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
        SDL_Rect rectBackground{ 550, worldHeight - 112, 880, 112 };
        SDL_RenderFillRect(renderer, &rectBackground);

        //Draw the heart image and the players amount of health.
        SDL_Rect rectHeart{ 560, worldHeight - 180, 170, 170 };
        SDL_RenderCopy(renderer, textureHeart, NULL, &rectHeart);
        drawText(renderer, 730, worldHeight - 65, 6, unitPlayer->getHealthString());

        //Draw the battery/ammo image and the players amount of ammo.
        SDL_Rect rectAmmo{ 860, worldHeight - 180, 170, 170 };
        SDL_RenderCopy(renderer, textureAmmo, NULL, &rectAmmo);
        drawText(renderer, 990, worldHeight - 65, 6, unitPlayer->computeAmmoString());

        //Draw the coin image and the players amount of coins.
        SDL_Rect rectCoin{ 1120, worldHeight - 180, 170, 170 };
        SDL_RenderCopy(renderer, textureCoin, NULL, &rectCoin);
        drawText(renderer, 1300, worldHeight - 65, 6, std::to_string(unitPlayer->getCountCoins()));

        //Draw the crosshair.  Assume that it's 16x16 pixels for simplicity.
        SDL_Rect rectCrosshair{ (worldWidth - 150) / 2, (worldHeight - 150) / 2, 150, 150 };
        SDL_RenderCopy(renderer, textureCrosshair, NULL, &rectCrosshair);

        // Draw "Enemies Remaining" or "Move To The Next Level" message
        std::string message;
        if (moveToNextLevelMessageTimer > 0) {
            message = "Move To The Next Level";
        }
        else {
            // int enemiesRemaining = Level::areaKillThreshold[Level::area-1] - Level::killCount;
            // message = "Enemies Remaining: " + std::to_string(enemiesRemaining);

            // if playing then display enemies remaining else go the flag
            if (Level::area < 5) {
                int enemiesRemaining = Level::areaKillThreshold[Level::area-1] - Level::killCount;
                message = "Enemies Remaining: " + std::to_string(enemiesRemaining);
            }
            else if (Level::area == 5 && Level::killCount < Level::areaKillThreshold[Level::area - 1]) {
                int enemiesRemaining = Level::areaKillThreshold[Level::area-1] - Level::killCount;
                message = "Enemies Remaining: " + std::to_string(enemiesRemaining);
            }
            else {
                message = "Go To The Flag To Win";
            }
        }

        drawText(renderer, 10, 10, 4, message);
    }
}

void Game::drawOverlayLevelIncrement(SDL_Renderer* renderer) {
    //Draw some text in the upper half of the screen that says level has been incremented
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_Rect rectBackground{ 0,0, worldWidth, worldHeight / 5 };
    SDL_RenderFillRect(renderer, &rectBackground);

    if (Level::area <= 4)
        drawText(renderer, 625, 50, 8, "Level Incremented");
    else 
        drawText(renderer, 625, 50, 8, "Exit Revealed");
}


void Game::drawOverlayVictory(SDL_Renderer* renderer) {
    //Draw a transparent green overlay that covers the whole screen.
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 160);
    SDL_Rect rectBackground{ 0,0, worldWidth, worldHeight };
    SDL_RenderFillRect(renderer, &rectBackground);

    //Draw the text.
    drawText(renderer, 730, 500, 12, "You Won!");
    drawText(renderer, 700, 600, 6, "-Press ESC to Quit-");
}


void Game::drawOverlayDefeat(SDL_Renderer* renderer) {
    //Draw a transparent red overlay that covers the whole screen.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 192);
    SDL_Rect rectBackground{ 0,0, worldWidth, worldHeight };
    SDL_RenderFillRect(renderer, &rectBackground);

    //Draw the text.
    drawText(renderer, 730, 500, 12, "You Lost!");
    drawText(renderer, 700, 600, 6, "-Press ESC to Quit-");
}



std::tuple<float,float, char> Game::raycast(Vector2D posStart, Vector2D normal, bool findWallFPlayerT) {
    //Start at the start position and move cell by cell on the level in the direction of the input normal.
    //If findWall then find the distance of the closest wall in the specified direction.
    //Otherwise check if the player is found before a wall (basically is the player visible from posStart or not).

    //Create some variables to be used as outputs.
    float distance = 0.0f;
    float fColor = 1.0f;

    //The fColor to be used for a corner.
    const float fColorCorner = 0.3f;

    //Determine how far the edge of the current cell is from posStart in the x direction.
    float deltaX = posStart.x - (int)posStart.x;
    //Ensure that the amount is correct depending on the direction of movement.  Invert it if needed.
    if (normal.x > 0.0f)
        deltaX = 1.0f - deltaX;

    //Do the same for the y direction.
    float deltaY = posStart.y - (int)posStart.y;
    if (normal.y > 0.0f)
        deltaY = 1.0f - deltaY;

    //The current integer position to check in the level.
    int iPosCheckX = (int)posStart.x, iPosCheckY = (int)posStart.y;


    bool firstCheck = true;
    bool checking = true;

    while (checking) {
        //Advance the position to be checked if needed.
        if (firstCheck == true) {
            //If this is the first check then don't advance iPosCheckX or iPosCheckY.
            firstCheck = false;
        }
        else {
            //If we move along the direction normal will the next cell be in the x or y direction?
            float ratioX = 1.0f;
            if (abs(normal.x) > 0.0f)
                ratioX = deltaX / abs(normal.x);

            float ratioY = 1.0f;
            bool ratioYSet = false;
            if (abs(normal.y) > 0.0f) {
                ratioY = deltaY / abs(normal.y);
                ratioYSet = true;
            }

            //Advance in the required direction.
            if (ratioX < ratioY || ratioYSet == false) {
                //The cell in the x direction is closer.
                iPosCheckX += (normal.x > 0 ? 1 : -1);
                deltaX = 1.0f;
                deltaY -= ratioX * abs(normal.y);

                distance += ratioX;

                //Update the color of the wall depending on if it's a corner or not.
                if (deltaY < 0.05f || deltaY > 0.95f)
                    fColor = fColorCorner;
                else
                    fColor = 1.0f;
            }
            else {
                //The cell in the y direction is closer.
                iPosCheckY += (normal.y > 0 ? 1 : -1);
                deltaX -= ratioY * abs(normal.x);
                deltaY = 1.0f;

                distance += ratioY;

                //Update the color of the wall depending on if it's a corner or not.
                if (deltaX < 0.05f || deltaX > 0.95f)
                    fColor = fColorCorner;
                else
                    fColor = 0.5f;
            }
        }


        //Check the specified position iPosCheck.
        int indexCheck = iPosCheckX + iPosCheckY * Level::levelWidth;
        if (indexCheck > -1 && indexCheck < Level::levelSize) {
            //Check if looking for a wall or the player
            if (findWallFPlayerT == false) {
                if (Level::levelData[indexCheck] == Level::symbolXWall)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'X');
                else if (Level::levelData[indexCheck] == Level::symbolYWall)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'Y');
                else if (Level::levelData[indexCheck] == Level::symbolZWall)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'Z');
                else if (Level::levelData[indexCheck] == Level::symbolJWall)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'J');
                else if (Level::levelData[indexCheck] == Level::symbolKWall)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'K');
                else if (Level::levelData[indexCheck] == Level::symbolDoorOne and Level::area == 1)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'L');
                else if (Level::levelData[indexCheck] == Level::symbolDoorTwo and Level::area == 2)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'M');
                else if (Level::levelData[indexCheck] == Level::symbolDoorThree and Level::area == 3)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'N');
                else if (Level::levelData[indexCheck] == Level::symbolDoorFour and Level::area == 4)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'O');
                else if (Level::levelData[indexCheck] == Level::symbolDoorFive and Level::area == 5)
                    //A wall was found so output it's distance and fColor.
                    return std::tuple<float, float, char>(distance, fColor, 'P');
                else
                    //No wall was found so ensure that the cell on listVisibleCells is set to true.
                    if (listVisibleCells[indexCheck] == false)
                        listVisibleCells[indexCheck] = true;
            }
            else {
                if (Level::levelData[indexCheck] == Level::symbolXWall or Level::levelData[indexCheck] == Level::symbolYWall or Level::levelData[indexCheck] == Level::symbolZWall or Level::levelData[indexCheck] == Level::symbolJWall or Level::levelData[indexCheck] == Level::symbolKWall or (Level::area == 1 and Level::levelData[indexCheck] == Level::symbolDoorOne) or (Level::area == 2 and Level::levelData[indexCheck] == Level::symbolDoorTwo) or (Level::area == 3 and Level::levelData[indexCheck] == Level::symbolDoorThree) or (Level::area == 4 and Level::levelData[indexCheck] == Level::symbolDoorFour))
                    //A wall was found before the player so stop checking.
                    checking = false;
                else if (unitPlayer != nullptr && iPosCheckX == (int)unitPlayer->getPos().x && 
                    iPosCheckY == (int)unitPlayer->getPos().y)
                    //No wall was found but the player was so output it's distance and a dummy fColor.
                    return std::tuple<float, float, char>(distance, 1.0f, '_');
            }
        }
        else
            //Out of bounds so stop checking.
            checking = false;
    }

    //Nothing was found so output a negative distance and fColor as 1.0f.
    return std::tuple<float, float, char>(-0.001f, 1.0f, '_');
}



void Game::drawWalls(SDL_Renderer* renderer) {
    if (worldWidth > 0 && unitPlayer != nullptr) {
        //Reset the list of visible cells so that none are visible anymore.
        std::fill(listVisibleCells.begin(), listVisibleCells.end(), false);

        //Loop through the width of the world/screen to draw the walls vertical line by vertical line.
        for (int count = 0; count < worldWidth; count++) {
            const float angleOffset = -fovRad / 2.0f + fovRad * (count / (float)(worldWidth - 1));
            //Determine the angle of the current vertical line to be drawn in the world.
            const float angleCurrent = unitPlayer->getAngle() + angleOffset;

            //Perform a raycast in the direction of the current vertical line to determine how far away it is.
            std::tuple<float, float, char> raycastData = raycast(unitPlayer->getPos(), Vector2D(angleCurrent), false);
            float distance = std::get<0>(raycastData);
            float fColor = std::get<1>(raycastData);
            char wallType = std::get<2>(raycastData);

            //Ensure that there wasn't an error eg. the player is somehow out of bounds of the world.
            if (distance > 0.0f) {
                //Set the color of the wall to be drawn.
                if (wallType == 'X')
                    SDL_SetRenderDrawColor(renderer, (int)round(50 * fColor), (int)round(50 * fColor), (int)round(50 * fColor), 255);
                else if (wallType == 'Y')
                    SDL_SetRenderDrawColor(renderer, (int)round(0 * fColor), (int)round(75 * fColor), (int)round(75 * fColor), 255);
                else if (wallType == 'Z')
                    SDL_SetRenderDrawColor(renderer, (int)round(85 * fColor), (int)round(30 * fColor), (int)round(30 * fColor), 255);
                else if (wallType == 'J')
                    SDL_SetRenderDrawColor(renderer, (int)round(75 * fColor), (int)round(75 * fColor), (int)round(0 * fColor), 255);
                else if (wallType == 'L' or wallType == 'M' or wallType == 'N' or wallType == 'O' or wallType == 'K')
                    SDL_SetRenderDrawColor(renderer, (int)round(150 * fColor), (int)round(75 * fColor), (int)round(0 * fColor), 255);
                else if (wallType == 'P')
                    SDL_SetRenderDrawColor(renderer, (int)round(0 * fColor), (int)round(255 * fColor), (int)round(0 * fColor), 255);

                //Determine the height of the vertical line to be drawn.
                float heightDraw = 1.0f * (atan(0.5f / distance) / fovRad * worldWidth * 2);
                //Set the depth/distance that the current line is away from the player/camera.
                listDepthDraw[count] = distance;

                //The position of the vertical line on the screen to be drawn.
                SDL_Rect rect = {
                    count,
                    (int)((worldHeight - heightDraw) / 2),
                    1,
                    (int)heightDraw };

                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}



void Game::addAllSpritesToDrawList(SDL_Renderer* renderer) {
    //Add any of the needed sprites to the draw list.
    for (std::shared_ptr<Sprite> enemy : listUnitEnemies)
        addSpriteToDrawList(enemy);

    for (std::shared_ptr<Sprite> pickup : listPickups)
        addSpriteToDrawList(pickup);

    for (std::shared_ptr<Sprite> projectile : listProjectiles)
        addSpriteToDrawList(projectile);

    addSpriteToDrawList(spriteFlag);
}



void Game::addSpriteToDrawList(std::shared_ptr<Sprite>& sprite) {
    if (unitPlayer != nullptr && sprite != nullptr) {
        //Check if the position of the sprite is visible.
        //Note that this is set by the raycast function when drawWalls is called.
        int indexCheck = (int)(sprite->getPos().x) + (int)(sprite->getPos().y) * Level::levelWidth;
        if (indexCheck > -1 && indexCheck < Level::levelSize &&
            listVisibleCells[indexCheck]) {
            float distance = (unitPlayer->getPos() - sprite->getPos()).magnitude();
            //Add the distance and sprite to the list.
            listSpritesToDraw.push_back(std::pair<float, std::weak_ptr<Sprite>>(
                distance, std::weak_ptr<Sprite>(sprite)));
        }
    }
}



void Game::sortAndDrawListSpritesToDraw(SDL_Renderer* renderer) {
    if (listSpritesToDraw.empty() == false) {
        //Sort the list based on the stored distances.
        std::sort(listSpritesToDraw.begin(), listSpritesToDraw.end(),
            [](auto a, auto b) { return (a.first < b.first); });

        //Loop through the list of sprites and draw them from furthest to closest.
        while (listSpritesToDraw.empty() == false) {
            std::pair<float, std::weak_ptr<Sprite>> dataSelected = listSpritesToDraw.back();
            if (auto spriteSelected = dataSelected.second.lock())
                spriteSelected->draw(renderer, worldWidth, worldHeight, unitPlayer, fovRad, listDepthDraw);

            listSpritesToDraw.pop_back();
        }
    }
}



void Game::drawText(SDL_Renderer* renderer, int offsetX, int offsetY, int size, std::string textToDraw) {
    if (textureFont != nullptr) {
        int cursorOffsetX = 0;
        //Loop through the textToDraw character by character.
        for (auto& charSelected : textToDraw) {
            //Get the ascii keycode for the selected character and find it's position in fontTexture.
            int charIDSelected = int(charSelected);
            int row = charIDSelected / 21;
            int column = charIDSelected % 21;

            //Draw the selected char in the correct spot at the correct size.
            SDL_Rect rSrc = { 1 + 6 * column, 1 + 8 * row, 5, 7 };
            SDL_Rect rDst = { offsetX + cursorOffsetX, offsetY, 5 * size, 7 * size };
            SDL_RenderCopy(renderer, textureFont, &rSrc, &rDst);

            //Advance the cursor.
            cursorOffsetX += 6 * size;
        }
    }
}



void Game::addRandomPickup(SDL_Renderer* renderer, Vector2D pos) {
    //Pick the index of a pickup to add at random.  Note if it's a value above 3 then it won't add anything.
    int index = rand() % (3 + 7);

    switch (index) {
    case 0:
        listPickups.push_back(std::make_shared<Health>(renderer, pos));
        break;
    case 1:
        listPickups.push_back(std::make_shared<Coin>(renderer, pos));
        break;
    case 2:
        listPickups.push_back(std::make_shared<Ammo>(renderer, pos));
        break;
    }
}

void Game::drawRedOverlay(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // Semi-transparent red
    SDL_Rect rectBackground{ 0, 0, worldWidth, worldHeight };
    SDL_RenderFillRect(renderer, &rectBackground);
}