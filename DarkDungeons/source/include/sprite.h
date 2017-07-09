//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_SPRITE_H
#define DARKDUNGEONS_SPRITE_H

#include <string>
#include <SDL.h>


class Graphics;

class Sprite {
public:
    Sprite();

    Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX,
           float posY);

    virtual ~Sprite();

    virtual void update();

    virtual void draw(Graphics &graphics, int x, int y);

protected:
    SDL_Texture *spriteSheet;
    SDL_Rect sourceRect;
    float x, y;
};

#endif //DARKDUNGEONS_SPRITE_H
