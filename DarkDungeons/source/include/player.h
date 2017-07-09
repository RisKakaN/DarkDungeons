//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_PLAYER_H
#define DARKDUNGEONS_PLAYER_H

#include "animatedSprite.h"

class Graphics;

class Player : public AnimatedSprite {
public:
    Player();

    Player(Graphics &graphics, Vector2 spawnPoint);

    void draw(Graphics &graphics);

    void update(float elapsedTime);

    // Moves up by -dy.
    void moveUp(float elapsedTime);

    // Moves down by dy.
    void moveDown(float elapsedTime);

    // Moves left by -dx.
    void moveLeft(float elapsedTime);

    // Moves right by dx.
    void moveRight(float elapsedTime);

    void stopMoving();

    virtual void setupAnimations();

private:
    Direction facing;

};


#endif //DARKDUNGEONS_PLAYER_H
