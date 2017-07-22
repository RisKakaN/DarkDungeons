//
// Created by Martin So on 2017-07-09.
//

#include <SDL2/SDL.h>
#include <algorithm>
#include <input.h>
#include <iostream>

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


    this->room = Room("Room1Center", "start", graphics);
    this->player = Player(graphics, this->room.getPlayerSpawnPoint());
    this->hud = Hud(graphics, this->player);

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
        } else if (input.isKeyHeld(SDL_SCANCODE_UP)) {
            this->player.moveUp(this->elapsedTime);
        } else if (input.isKeyHeld(SDL_SCANCODE_DOWN)) {
            this->player.moveDown(this->elapsedTime);
        } else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
            this->player.moveLeft(this->elapsedTime);
        } else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
            this->player.moveRight(this->elapsedTime);
        }

        // Interactions.
        if (input.isKeyHeld(SDL_SCANCODE_A)) {
            this->player.interact();
        }

        // Stop interaction.
        if(input.wasKeyReleased(SDL_SCANCODE_A)) {
            this->player.stopInteract();
        }

        if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)
            && !input.isKeyHeld(SDL_SCANCODE_UP) && !input.isKeyHeld(SDL_SCANCODE_DOWN)) {
            this->player.stopMoving();
        }

        const float CURRENT_TIME_MS = SDL_GetTicks();
        float ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        // Store the graphics.
        this->graphics = graphics;
        this->update(ELAPSED_TIME_MS);
        this->elapsedTime = ELAPSED_TIME_MS;

        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw(graphics);
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear();

    this->room.draw(graphics);
    this->player.draw(graphics);
    this->hud.draw(graphics);

    graphics.flip();
}

void Game::update(float elapsedTime) {
    this->player.update(elapsedTime);
    this->room.update(elapsedTime, this->player);
    this->hud.update(elapsedTime);

    //Check collisions
    std::vector<Rectangle> others;
    if ((others = this->room.checkTileCollisions(this->player.getBoundingBox())).size() > 0) {
        //Player collided with at least one tile. Handle it.
        this->player.handleTileCollisions(others);
    }

    // Check doors
    std::vector<Door> otherDoors;
    // Same as: assign to otherDoors, then check otherDoors > 0
    if((otherDoors = this->room.checkDoorCollisions(this->player.getBoundingBox())).size() > 0) {
        this->player.handleDoorCollision(otherDoors, this->room, this->graphics);
    }
}