//
// Created by Martin So on 2017-07-09.
//

#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "globals.h"

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(game_constants::SCREEN_WIDTH, game_constants::SCREEN_HEIGHT, 0, &this->window, &this->renderer);
    SDL_SetWindowTitle(this->window, "Dark Dungeons");
}

Graphics::~Graphics() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}

SDL_Surface *Graphics::loadImage(const std::string &filePath) {
    if(this->spriteSheets.count(filePath) == 0) {
        this->spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle) {
    SDL_RenderCopy(this->renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
    SDL_RenderPresent(this->renderer);
}

void Graphics::clear() {
    SDL_RenderClear(this->renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return this->renderer;
}