#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Player; //forward dec.

class Renderer {
public:
    void setRenderer(SDL_Renderer* renderer);
    void render(const Player& player);

private:
    SDL_Renderer* renderer;
};

#endif
