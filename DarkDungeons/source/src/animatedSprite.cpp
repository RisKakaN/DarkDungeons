//
// Created by Martin So on 2017-07-09.
//

#include "animatedsprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width,
                               int height, float posX, float posY, float timeToUpdate) :
        Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY), frameIndex(0), timeElapsed(0),
        timeToUpdate(timeToUpdate), visible(true), currentAnimationOnce(false),
        currentAnimation("") {}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
    std::vector<SDL_Rect> rectangles;
    for (int i = 0; i < frames; i++) {
        SDL_Rect newRect = {(i + x) * width, y * height, width, height};
        rectangles.push_back(newRect);
    }
    this->animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
    this->offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
    this->currentAnimationOnce = once;
    if (this->currentAnimation != animation) {
        this->currentAnimation = animation;
        this->frameIndex = 0;
    }
}


void AnimatedSprite::setVisible(bool visible) {
    this->visible = visible;
}

void AnimatedSprite::stopAnimation() {
    this->frameIndex = 0;
}

void AnimatedSprite::update(float elapsedTime) {
    Sprite::update();

    this->timeElapsed += elapsedTime;
    if (this->timeElapsed > this->timeToUpdate) {
        this->timeElapsed -= this->timeToUpdate;
        if (this->frameIndex < this->animations[this->currentAnimation].size() - 1) {
            this->frameIndex++;
        } else {
            if (this->currentAnimationOnce) {
                this->setVisible(false);
            }
            stopAnimation();
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y) {
    if (this->visible) {
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x + this->offsets[this->currentAnimation].x;
        destinationRectangle.y = y + this->offsets[this->currentAnimation].y;
        destinationRectangle.w = this->sourceRect.w * game_constants::SPRITE_SCALE;
        destinationRectangle.h = this->sourceRect.h * game_constants::SPRITE_SCALE;


        SDL_Rect sourceRect = this->animations[this->currentAnimation][this->frameIndex];
        graphics.blitSurface(this->spriteSheet, &sourceRect, &destinationRectangle);
    }
}

void AnimatedSprite::setupAnimations() {
    this->addAnimation(2, 6, 0, "RunLeft", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    this->addAnimation(2, 4, 0, "RunRight", game_constants::SPRITE_FRAME_SIZE, game_constants::SPRITE_FRAME_SIZE,
                       Vector2(0, 0));
    }