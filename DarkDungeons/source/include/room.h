//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_ROOM_H
#define DARKDUNGEONS_ROOM_H

#include <string>
#include <vector>

#include "globals.h"
#include "tile.h"

class Graphics;

struct SDL_Rect;
struct Tileset;

class Room {
public:
    Room();

    // Take in file name.
    Room(std::string roomName, Vector2 spawnPoint, Graphics &graphics);

    ~Room();

    void update(float elapsedTime);

    void draw(Graphics &graphics);

    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);

    const Vector2 getPlayerSpawnPoint() const;

private:
    std::string roomName;
    Vector2 spawnPoint;

    Vector2 size;
    Vector2 tileSize;

    SDL_Texture *backgroundTexture;

    std::vector<Tile> tileList;
    std::vector<Tileset> tilesets;
    std::vector<Rectangle> collisionRects;

    void loadMap(std::string roomName, Graphics &graphics);
};

// Tileset structure
struct Tileset {
    SDL_Texture *Texture;
    int FirstGid;

    Tileset() {
        this->FirstGid = -1;
    }

    Tileset(SDL_Texture *texture, int firstGid) {
        this->Texture = texture;
        this->FirstGid = firstGid;
    }
};

#endif //DARKDUNGEONS_ROOM_H
