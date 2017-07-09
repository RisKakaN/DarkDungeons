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

    this->boundingBox = Rectangle(this->x, this->y, width * game_constants::SPRITE_SCALE,
                                  height * game_constants::SPRITE_SCALE);
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
    SDL_Rect destinationRectangle = {x, y, this->sourceRect.w * game_constants::SPRITE_SCALE,
                                     this->sourceRect.h * game_constants::SPRITE_SCALE};
    graphics.blitSurface(this->spriteSheet, &this->sourceRect, &destinationRectangle);
}

void Sprite::update() {
    this->boundingBox = Rectangle(this->x, this->y, this->sourceRect.w * game_constants::SPRITE_SCALE,
                                  this->sourceRect.h * game_constants::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const {
    return this->boundingBox;
}

// Determine which side the collision happened on.
// Smallest amount equals the side the collision happened on.
const sides::Side Sprite::getCollisionSide(Rectangle &other) const {
    int amountRight, amountLeft, amountTop, amountBottom;
    amountRight = this->getBoundingBox().getWest() - other.getWest();
    amountLeft = other.getEast() - this->getBoundingBox().getWest();
    amountTop = other.getSouth() - this->getBoundingBox().getNorth();
    amountBottom = this->getBoundingBox().getSouth() - other.getNorth();

    // Find lowest. Loop through.
    int vals[4] = {abs(amountRight), abs(amountLeft), abs(amountTop), abs(amountBottom)};
    int lowest = vals[0];
    for (int i = 0; i < 4; i++) {
        if (vals[i] < lowest) {
            lowest = vals[i];
        }
    }
    return lowest == abs(amountRight) ? sides::EAST :
           lowest == abs(amountLeft) ? sides::WEST :
           lowest == abs(amountTop) ? sides::NORTH :
           lowest == abs(amountBottom) ? sides::SOUTH :
           sides::NONE;
}