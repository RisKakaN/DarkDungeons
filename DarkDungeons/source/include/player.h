//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_PLAYER_H
#define DARKDUNGEONS_PLAYER_H

#include "animatedSprite.h"
#include "door.h"
#include "room.h"

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

    void interact();

    void stopInteract();

    virtual void setupAnimations();

    void handleTileCollisions(std::vector<Rectangle> &others);

    void handleDoorCollision(std::vector<Door> &others, Room &room, Graphics &graphics);

    const inline int getPlayerX() const {
        return this->x;
    }

    const inline int getPlayerY() const {
        return this->y;
    }

private:
    Direction facing;

    bool isInteracting;

};


#endif //DARKDUNGEONS_PLAYER_H
