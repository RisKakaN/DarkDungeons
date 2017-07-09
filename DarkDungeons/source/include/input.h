//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_INPUT_H
#define DARKDUNGEONS_INPUT_H


#include <SDL.h>
#include <map>

class Input {
public:
    void beginNewFrame();

    void keyUpEvent(const SDL_Event &event);

    void keyDownEvent(const SDL_Event &event);

    bool wasKeyPressed(SDL_Scancode key);

    bool wasKeyReleased(SDL_Scancode key);

    bool isKeyHeld(SDL_Scancode key);

private:
    std::map<SDL_Scancode, bool> heldKeys;
    std::map<SDL_Scancode, bool> pressedKeys;
    std::map<SDL_Scancode, bool> releasedKeys;

};

#endif //DARKDUNGEONS_INPUT_H
