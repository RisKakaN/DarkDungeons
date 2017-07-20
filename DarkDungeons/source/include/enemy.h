//
// Created by Martin So on 2017-07-20.
//

#ifndef DARKDUNGEONS_ENEMY_H
#define DARKDUNGEONS_ENEMY_H

#include "animatedSprite.h"
#include "globals.h"
#include "player.h"

#include <string>

class Graphics;

class Enemy : public AnimatedSprite {
public:
    Enemy();
    Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate);
    virtual ~Enemy();
    virtual void update(float elapsedTime, Player &player);
    virtual void draw(Graphics &graphics);

    // Checking area: 5x5 tiles.
    bool playerInRange(Player &player);

    void moveToPlayer(float elapsedTime, Player &player);

    // Moves up by -dy.
    void moveUp(float elapsedTime);

    // Moves down by dy.
    void moveDown(float elapsedTime);

    // Moves left by -dx.
    void moveLeft(float elapsedTime);

    // Moves right by dx.
    void moveRight(float elapsedTime);

    void stopMoving();

    const inline int getMaxHealth() const {
        return this->maxHealth;
    }

    const inline int getCurrentHealth() const {
        return this->currentHealth;
    }

protected:
    Direction direction;

    int maxHealth;
    int currentHealth;

private:
    bool chasing;
};

#endif //DARKDUNGEONS_ENEMY_H
