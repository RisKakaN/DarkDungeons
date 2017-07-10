//
// Created by Martin So on 2017-07-10.
//

#ifndef DARKDUNGEONS_DOOR_H
#define DARKDUNGEONS_DOOR_H

#include <string>
#include "rectangle.h"

class Door : public Rectangle {
public:
    Door() {}

    Door(Rectangle r, std::string destination) :
            Rectangle(r.getWest() * game_constants::SPRITE_SCALE, r.getNorth() * game_constants::SPRITE_SCALE,
                      r.getWidth() * game_constants::SPRITE_SCALE, r.getHeight() * game_constants::SPRITE_SCALE),
            destination(destination) {}

    const inline std::string getDestination() const {
        return this->destination;
    }

private:
    std::string destination;
};

#endif //DARKDUNGEONS_DOOR_H
