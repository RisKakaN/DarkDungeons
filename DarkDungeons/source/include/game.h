//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_GAME_H
#define DARKDUNGEONS_GAME_H

#include "animatedSprite.h"
#include "player.h"
#include "room.h"
#include "graphics.h"
#include "hud.h"

class Game {
public:
    Game();

    ~Game();

private:
    void gameLoop();

    void draw(Graphics &graphics);

    void update(float elapsedTime);

    float elapsedTime;

    Player player;

    Room room;

    Hud hud;

    Graphics graphics;
};

#endif //DARKDUNGEONS_GAME_H
