//
// Created by Martin So on 2017-07-20.
//

#include <enemyLevel1.h>
#include <iostream>

EnemyLevel1::EnemyLevel1() {}

EnemyLevel1::EnemyLevel1(Graphics &graphics, Vector2 spawnPoint) : Enemy(graphics, "content/sprites/enemies1.png", 0, 0,
                                                                         16, 16, spawnPoint, 100) {
    this->setupAnimations();
    this->playAnimation("IdleDown");
}

EnemyLevel1::~EnemyLevel1() {}

void EnemyLevel1::update(float elapsedTime, Player &player) {
    this->moveToPlayer(elapsedTime, player);
    Enemy::update(elapsedTime, player);
}

void EnemyLevel1::draw(Graphics &graphics) {
    Enemy::draw(graphics);
}

void EnemyLevel1::setupAnimations() {
    this->addAnimation(2, 2, 0, "RunUp", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(2, 0, 0, "RunDown", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(2, 6, 0, "RunLeft", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(2, 4, 0, "RunRight", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(1, 2, 0, "IdleUp", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(1, 0, 0, "IdleDown", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(1, 6, 0, "IdleLeft", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(1, 4, 0, "IdleRight", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
}