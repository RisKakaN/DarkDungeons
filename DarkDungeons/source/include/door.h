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

    Door(Rectangle r, std::string destination, std::string position) :
            Rectangle(r.getWest() * game_constants::TILE_SCALE, r.getNorth() * game_constants::TILE_SCALE,
                      r.getWidth() * game_constants::TILE_SCALE, r.getHeight() * game_constants::TILE_SCALE),
            destination(destination),
            position(position) {}

    const inline std::string getDestination() const {
        return this->destination;
    }

    const inline std::string getPosition() const {
        return this->position;
    }

private:
    std::string destination;
    std::string position;
};

#endif //DARKDUNGEONS_DOOR_H
