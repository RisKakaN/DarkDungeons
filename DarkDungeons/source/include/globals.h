//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_GLOBALS_H
#define DARKDUNGEONS_GLOBALS_H

namespace game_constants {
    const int SCREEN_WIDTH = 720;
    const int SCREEN_HEIGHT = 480;

    const int SPRITE_SCALE = 2;
    const int TILE_SCALE = 1;
    const int SPRITE_FRAME_SIZE = 16;
}

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

namespace sides {
    enum Side {
        NORTH,
        SOUTH,
        WEST,
        EAST,
        NONE
    };
}

struct Vector2 {
    int x, y;

    Vector2() : x(0), y(0) {}

    Vector2(int x, int y) : x(x), y(y) {}
};

#endif //DARKDUNGEONS_GLOBALS_H
