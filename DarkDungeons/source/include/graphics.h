//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_GRAPHICS_H
#define DARKDUNGEONS_GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();

    ~Graphics();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif //DARKDUNGEONS_GRAPHICS_H
