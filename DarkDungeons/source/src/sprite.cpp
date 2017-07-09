//
// Created by Martin So on 2017-07-09.
//

#include "globals.h"
#include "sprite.h"
#include "graphics.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
               float posX, float posY) : x(posX), y(posY) {
    this->sourceRect.x = sourceX;
    this->sourceRect.y = sourceY;
    this->sourceRect.w = width;
    this->sourceRect.h = height;

    this->spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (this->spriteSheet == NULL) {
        printf("\nError: Unable to load image\n");
    }
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
    SDL_Rect destinationRectangle = {x, y, this->sourceRect.w * game_constants::SPRITE_SCALE,
                                     this->sourceRect.h * game_constants::SPRITE_SCALE};
    graphics.blitSurface(this->spriteSheet, &this->sourceRect, &destinationRectangle);
}

void Sprite::update() {
}