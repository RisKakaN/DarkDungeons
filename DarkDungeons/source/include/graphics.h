//
// Created by Martin So on 2017-07-09.
//

#ifndef DARKDUNGEONS_GRAPHICS_H
#define DARKDUNGEONS_GRAPHICS_H

#include <string>
#include <map>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();

    ~Graphics();

    SDL_Surface *loadImage(const std::string &filePath);

    // Draws a texture to a certain part of the screen.
    void blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle);

    // Renders everything to the screen.
    void flip();

    // Clears the screen.
    void clear();

    SDL_Renderer *getRenderer() const;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Access SDL surfaces by names (string).
    std::map<std::string, SDL_Surface *> spriteSheets;
};

#endif //DARKDUNGEONS_GRAPHICS_H
