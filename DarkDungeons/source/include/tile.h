//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_TILE_H
#define DARKDUNGEONS_TILE_H


#include "globals.h"

struct SDL_Texture;
class Graphics;

class Tile {
public:
    Tile();

    Tile(SDL_Texture *tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);

    void update(float elapsedTime);

    void draw(Graphics &graphics);

protected:
    SDL_Texture* tileset;
    Vector2 size;
    Vector2 tilesetPosition;
    Vector2 position;
};

#endif //DARKDUNGEONS_TILE_H
