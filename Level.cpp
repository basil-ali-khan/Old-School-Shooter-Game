#include "Level.h"
// #include "UnitEnemy.h"


const char* Level::levelData{
    "XXXXXXXXXX"
    "X        X"
    "X  S     X"
    "X        X"
    "XXXXXXXXXX"


};

const int Level::levelWidth = 10;
const size_t Level::levelSize = strlen(levelData);



bool Level::isBlockAtPos(int x, int y) {
    int index = x + y * levelWidth;
    if (index > -1 && index < levelSize)
        return (levelData[index] == symbolWall);

    return false;
}



void Level::setupStartandFinish(SDL_Renderer* renderer, Vector2D& posStart, Vector2D& posFinish ) {
    for (int index = 0; index < levelSize; index++) {
        //The current position in the level in Vector2D form.
        Vector2D pos(
            (float)(index % levelWidth) + 0.5f,
            (float)(index / levelWidth) + 0.5f);

        //Check if any of the following symbols are found and modify the input positions and lists as required.
        switch (levelData[index]) {
        case symbolStart:
            posStart = pos;
            break;
        case symbolFinish:
            posFinish = pos;
            break;
        }
    }
}