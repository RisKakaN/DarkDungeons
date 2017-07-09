//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_RECTANGLE_H
#define DARKDUNGEONS_RECTANGLE_H

#include "globals.h"

// Do not need cpp file because it is small and it is nice to have everything in the same file.
class Rectangle {
public:
    Rectangle() {}

    Rectangle(int x, int y, int width, int height) :
            x(x), y(y), width(width), height(height) {}

    const int getWest() const {
        return this->x;
    }

    const int getEast() const {
        return this->x + this->width;
    }

    const int getNorth() const {
        return this->y;
    }

    const int getSouth() const {
        return this->y + this->height;
    }

    const int getWidth() const {
        return this->width;
    }

    const int getHeight() const {
        return this->height;
    }

    // Takes another Rectangle and checks if the two are colliding.
    const bool collidesWith(const Rectangle &other) const {
        return this->getEast() >= other.getWest() &&
               this->getWest() <= other.getEast() &&
               this->getNorth() <= other.getSouth() &&
               this->getSouth() >= other.getNorth();
    }

    const inline Rectangle getRect() const {
        return *this;
    }

private:
    int x, y, width, height;

};

#endif //DARKDUNGEONS_RECTANGLE_H
