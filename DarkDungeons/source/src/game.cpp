//
// Created by Martin So on 2017-07-09.
//

#include <SDL2/SDL.h>
#include <algorithm>
#include <input.h>

#include "game.h"
#include "graphics.h"

// Game loop constants
namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    float LAST_UPDATE_TIME = SDL_GetTicks();

    // Temporary elapsed time.
    elapsedTime = MAX_FRAME_TIME;

    //Start the game loop
    while (true) {

        input.beginNewFrame();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                // Check if key not held down
                if (event.key.repeat == 0) {
                    input.keyDownEvent(event);
                }
            } else if (event.type == SDL_KEYUP) {
                input.keyUpEvent(event);
            } else if (event.type == SDL_QUIT) {
                return;
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
            return;
        }

        const float CURRENT_TIME_MS = SDL_GetTicks();
        float ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
    }
}

void Game::draw(Graphics &graphics) {

}

void Game::update(float elapsedTime) {

}