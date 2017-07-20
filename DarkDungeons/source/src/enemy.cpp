//
// Created by Martin So on 2017-07-20.
//

#include <enemy.h>
#include <cmath>
#include <iostream>

namespace enemy_constants {
    const float WALK_SPEED = 0.1f;
}

Enemy::Enemy() {}

Enemy::Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height,
             Vector2 spawnPoint, int timeToUpdate) :
        AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate),
        direction(DOWN), maxHealth(0), currentHealth(0), chasing(false) {}

Enemy::~Enemy() {}

void Enemy::update(float elapsedTime, Player &player) {
    AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics &graphics) {
    AnimatedSprite::draw(graphics, this->x, this->y);
}

bool Enemy::playerInRange(Player &player) {
    if(chasing) {
        return true;
    }
    if (std::fabs(this->x - player.getPlayerX()) <= 5 * game_constants::SPRITE_FRAME_SIZE &&
        std::fabs(this->y - player.getPlayerY() <= 5 * game_constants::SPRITE_FRAME_SIZE)) {
        chasing = true;
        return true;
    }
}

void Enemy::moveToPlayer(float elapsedTime, Player &player) {
    if (playerInRange(player)) {
        if (this->x < player.getPlayerX()) {
            this->moveRight(elapsedTime);
        } else if (this->x > player.getPlayerX()) {
            this->moveLeft(elapsedTime);
        }
        if (this->y < player.getPlayerY()) {
            this->moveDown(elapsedTime);
        } else if (this->y > player.getPlayerY()) {
            this->moveUp(elapsedTime);
        }
    }
}

void Enemy::moveUp(float elapsedTime) {
    this->y -= enemy_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunUp");
    this->direction = UP;
}

void Enemy::moveDown(float elapsedTime) {
    this->y += enemy_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunDown");
    this->direction = DOWN;
}

void Enemy::moveLeft(float elapsedTime) {
    this->x -= enemy_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunLeft");
    this->direction = LEFT;
}

void Enemy::moveRight(float elapsedTime) {
    this->x += enemy_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunRight");
    this->direction = RIGHT;
}

void Enemy::stopMoving() {
    switch (this->direction) {
        case UP:
            playAnimation("IdleUp");
            break;
        case DOWN:
            playAnimation("IdleDown");
            break;
        case LEFT:
            playAnimation("IdleLeft");
            break;
        case RIGHT:
            playAnimation("IdleRight");
            break;
    }
}