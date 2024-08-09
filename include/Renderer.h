#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <list>
#include <list>

class Player; //forward dec.
class Bullet;
class Astreoid;

class Renderer {
public:
    void setRenderer(SDL_Renderer* renderer);
    void render(const Player& player, std::list<Bullet>& activeBullets, std::list<Astreoid>& astreoids);

private:
    SDL_Renderer* renderer;
};

#endif
