#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>

class Player; //forward dec.
class Bullet;
class Astreoid;

class Renderer {
public:
    void setRenderer(SDL_Renderer* renderer);
    void render(const Player& player, std::vector<Bullet>& activeBullets, std::vector<Astreoid>& astreoids);

private:
    SDL_Renderer* renderer;
};

#endif
