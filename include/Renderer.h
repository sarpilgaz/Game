#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>

class Player; //forward dec.
class Bullet;

class Renderer {
public:
    void setRenderer(SDL_Renderer* renderer);
    void render(const Player& player, std::vector<Bullet>& activeBullets);

private:
    SDL_Renderer* renderer;
};

#endif
