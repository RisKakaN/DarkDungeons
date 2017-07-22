//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_SPRITE_H
#define DARKDUNGEONS_SPRITE_H

#include <string>
#include <SDL.h>

#include "rectangle.h"
#include "globals.h"


class Graphics;

class Sprite {
public:
    Sprite();

    Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX,
           float posY);

    virtual ~Sprite();

    virtual void update();

    virtual void draw(Graphics &graphics, int x, int y);

    const Rectangle getBoundingBox() const;

    const sides::Side getCollisionSide(Rectangle &other) const;

    const inline float getX() const {
        return this->x;
    }

    const inline float getY() const {
        return this->y;
    }

    void setSourceRectX(int value);
    void setSourceRectY(int value);
    void setSourceRectW(int value);
    void setSourceRectH(int value);

protected:
    SDL_Texture *spriteSheet;
    SDL_Rect sourceRect;

    Rectangle boundingBox;

    float x, y;
};

#endif //DARKDUNGEONS_SPRITE_H
