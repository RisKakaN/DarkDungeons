//
// Created by Martin So on 2017-07-09.
//

#include <room.h>

Room::Room() {}

Room::Room(std::string roomName, Vector2 spawnpoint, Graphics &graphics) :
        roomName(roomName),
        spawnPoint(spawnPoint),
        size(Vector2(0, 0)) {
    this->loadMap(roomName, graphics);
}

Room::~Room() {}

void Room::loadMap(std::string mapName, Graphics &graphics) {
    //TEMPORARY CODE TO LOAD THE BACKGROUND
    this->backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
                                                           graphics.loadImage("content/bkBlue.png"));
    this->size = Vector2(1280, 720);
}

void Room::update(float elapsedTime) {

}

void Room::draw(Graphics &graphics) {
    //Draw the background
    SDL_Rect sourceRect = {0, 0, 64, 64};
    SDL_Rect destRect;
    for (int x = 0; x < this->size.x / 64; x++) {
        for (int y = 0; y < this->size.y / 64; y++) {
            destRect.x = x * 64;
            destRect.y = y * 64;
            destRect.w = 64;
            destRect.h = 64;
            graphics.blitSurface(this->backgroundTexture, &sourceRect, &destRect);
        }
    }
}