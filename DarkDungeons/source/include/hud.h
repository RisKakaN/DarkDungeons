//
// Created by Martin So on 2017-07-21.
//

#ifndef DARKDUNGEONS_HUD_H
#define DARKDUNGEONS_HUD_H

#include "sprite.h"
#include "player.h"

class Graphics;

class Hud {
public:
    Hud();
    Hud(Graphics &graphics, Player &player);
    void update(float elapsedTime);
    void draw(Graphics &graphics);

private:
    Player player;

    Sprite healthBackgroundBarSprite;
    Sprite healthBarSprite;
    Sprite manaBackgroundBarSprite;
    Sprite manaBarSprite;
    Sprite expBackgroundBarSprite;
    Sprite expBarSprite;
};

#endif //DARKDUNGEONS_HUD_H
