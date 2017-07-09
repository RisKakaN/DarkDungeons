//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_ROOM_H
#define DARKDUNGEONS_ROOM_H

#include <string>
#include "globals.h"
#include "graphics.h"

class Room {
public:
    Room();

    // Take in file name.
    Room(std::string roomName, Vector2 spawnPoint, Graphics &graphics);

    ~Room();

    void update(float elapsedTime);

    void draw(Graphics &graphics);

private:
    std::string roomName;
    Vector2 spawnPoint;

    Vector2 size;
    SDL_Texture *backgroundTexture;

    void loadMap(std::string roomName, Graphics &graphics);
};

#endif //DARKDUNGEONS_ROOM_H
