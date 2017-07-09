//
// Created by Martin So on 2017-07-09.
//

#include <SDL.h>

#include "graphics.h"

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(1280, 720, 0, &this->window, &this->renderer);
    SDL_SetWindowTitle(this->window, "Dark Dungeons");
}

Graphics::~Graphics() {
    SDL_DestroyWindow(this->window);
}