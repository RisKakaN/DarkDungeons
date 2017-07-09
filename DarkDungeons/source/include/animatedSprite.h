//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_ANIMATEDSPRITE_H
#define DARKDUNGEONS_ANIMATEDSPRITE_H

#include "sprite.h"
#include "globals.h"

#include <map>
#include <string>
#include <vector>

class Graphics;

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();

    // Takes in: graphics, file, start x and y positions in sprite,
    // width and height of sprite, spawnpoint x and y, update speed of frame.
    AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
                   float posX, float posY, float timeToUpdate);

    void playAnimation(std::string animation, bool once = false);

    virtual void update(float elapsedTime);

    void draw(Graphics &graphics, int x, int y);



protected:
    double timeToUpdate;
    bool currentAnimationOnce;
    std::string currentAnimation;

    // Takes in: amount of frames in the movement,
    // start x and y position (count as number of frames instead of pixels)
    // name of movement, width and height of frame, offset
    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

    void stopAnimation();

    void setVisible(bool visible);

    virtual void setupAnimations() = 0;

private:
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, Vector2> offsets;

    int frameIndex;
    double timeElapsed;
    bool visible;
};

#endif //DARKDUNGEONS_ANIMATEDSPRITE_H
