#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Renderer {
public:
    void setRenderer(SDL_Renderer* renderer);
    void render();

private:
    SDL_Renderer* renderer;
};

#endif
