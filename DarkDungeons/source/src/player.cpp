//
// Created by Martin So on 2017-07-09.
//

#include "player.h"
#include "globals.h"


namespace player_constants {
    const float WALK_SPEED = 0.3f;
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint) : AnimatedSprite(graphics, "content/sprites/Characters.png", 0,
                                                                        4 * game_constants::SPRITE_FRAME_SIZE, 16, 16,
                                                                        spawnPoint.x, spawnPoint.y, 100),
                                                         facing(RIGHT), isInteracting(false) {
    this->setupAnimations();
}

void Player::setupAnimations() {
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

void Player::moveUp(float elapsedTime) {
    this->y -= player_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunUp");
    this->facing = UP;
}

void Player::moveDown(float elapsedTime) {
    this->y += player_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunDown");
    this->facing = DOWN;
}

void Player::moveLeft(float elapsedTime) {
    this->x -= player_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunLeft");
    this->facing = LEFT;
}

void Player::moveRight(float elapsedTime) {
    this->x += player_constants::WALK_SPEED * elapsedTime;
    this->playAnimation("RunRight");
    this->facing = RIGHT;
}

void Player::stopMoving() {
    switch (this->facing) {
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

void Player::interact() {
    this->isInteracting = true;
    // TODO: Might need some animation.
}

void Player::stopInteract() {
    this->isInteracting = false;
}

// Handles collisions with ALL tiles the player is colliding with.
void Player::handleTileCollisions(std::vector<Rectangle> &others) {
    // Figure out what side the collision happened on and move the player accordingly.
    for (int i = 0; i < others.size(); i++) {
        sides::Side collisionSide = this->getCollisionSide(others.at(i));
        if (collisionSide != sides::NONE) {
            switch (collisionSide) {
                case sides::NORTH :
                    this->y = others.at(i).getSouth() + 1;
                    break;
                case sides::SOUTH:
                    this->y = others.at(i).getNorth() - this->boundingBox.getHeight() - 1;
                    break;
                case sides::WEST:
                    this->x = others.at(i).getEast() + 1;
                    break;
                case sides::EAST:
                    this->x = others.at(i).getWest() - this->boundingBox.getWidth() - 1;
            }
        }
    }
}

void Player::handleDoorCollision(std::vector<Door> &others, Room &room, Graphics &graphics) {
    //Check if the player is grounded and holding the down arrow.
    // If so, go through the door, else do nothing.
    for (int i = 0; i < others.size(); i++) {
        if(this->isInteracting) {
            room = Room(others.at(i).getDestination(), graphics);
            this->x = room.getPlayerSpawnPoint().x;
            this->y = room.getPlayerSpawnPoint().y;
        }
    }
}

void Player::update(float elapsedTime) {
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
    AnimatedSprite::draw(graphics, this->x, this->y);
}