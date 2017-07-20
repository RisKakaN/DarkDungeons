//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_ROOM_H
#define DARKDUNGEONS_ROOM_H

#include <string>
#include <vector>

#include "globals.h"
#include "tile.h"
#include "door.h"

class Graphics;

struct SDL_Rect;
struct Tileset;

class Room {
public:
    Room();

    // Take in file name.
    Room(std::string roomName, std::string spawnPosition, Graphics &graphics);

    ~Room();

    void update(float elapsedTime);

    void draw(Graphics &graphics);

    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    std::vector<Door> checkDoorCollisions(const Rectangle &other);

    const Vector2 getPlayerSpawnPoint() const;

private:
    std::string roomName;
    std::string spawnPosition;

    Vector2 spawnPointStart;
    // Spawn position is determined by which door the player arrives to.
    Vector2 spawnPointNorth;
    Vector2 spawnPointSouth;
    Vector2 spawnPointWest;
    Vector2 spawnPointEast;

    Vector2 size;
    Vector2 tileSize;

    std::vector<Tile> tileList;
    std::vector<Tileset> tilesets;
    std::vector<Rectangle> collisionRects;

    std::vector<Door> doorList;

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
