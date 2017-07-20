//
// Created by Martin So on 2017-07-20.
//

#ifndef DARKDUNGEONS_ENEMYLEVEL1_H
#define DARKDUNGEONS_ENEMYLEVEL1_H

#include "enemy.h"

class EnemyLevel1 : public Enemy {
public:
    EnemyLevel1();
    EnemyLevel1(Graphics &graphics, Vector2 spawnPoint);
    ~EnemyLevel1();
    void update(float elapsedTime, Player &player);
    void draw(Graphics &graphics);

    void setupAnimations();
};

#endif //DARKDUNGEONS_ENEMYLEVEL1_H
