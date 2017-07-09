//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_GAME_H
#define DARKDUNGEONS_GAME_H

#include "sprite.h"

class Graphics;

class Game {
public:
    Game();

    ~Game();

private:
    void gameLoop();

    void draw(Graphics &graphics);

    void update(float elapsedTime);

    float elapsedTime;

    Sprite player;
};

#endif //DARKDUNGEONS_GAME_H
