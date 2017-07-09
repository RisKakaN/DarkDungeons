//
// Created by Martin So on 2017-07-09.
//

#include "tile.h"
#include "graphics.h"

Tile::Tile() {}

Tile::Tile(SDL_Texture *tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
        tileset(tileset), size(size), tilesetPosition(tilesetPosition),
        position(Vector2(position.x * game_constants::SPRITE_SCALE, position.y * game_constants::SPRITE_SCALE)) {}

void Tile::update(float elapsedTime) {}

void Tile::draw(Graphics &graphics) {
    SDL_Rect desRect = {this->position.x, this->position.y, this->size.x * game_constants::SPRITE_SCALE,
                        this->size.y * game_constants::SPRITE_SCALE};
    SDL_Rect sourceRect = {this->tilesetPosition.x, this->tilesetPosition.y, this->size.x, this->size.y};

    graphics.blitSurface(this->tileset, &sourceRect, &desRect);
}