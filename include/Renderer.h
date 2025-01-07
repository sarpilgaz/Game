#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include <string>
#include "StateManager.h"

class Player; //forward dec.
class Bullet;
class Astreoid;

class Renderer {
public:
    Renderer(StateManager& sm) : stateManager(sm) {}
    void setRenderer(SDL_Renderer* renderer);
    void render(const Player& player, std::list<Bullet>& activeBullets, std::list<Astreoid>& astreoids);

private:
    SDL_Renderer* renderer;
    StateManager& stateManager;
    void prepareRender();
    void renderGame(const Player& player, std::list<Bullet>& activeBullets, std::list<Astreoid>& astreoids);
    void renderText(const char* text, int xPos, int yPos);
    void renderGameOver();
};

#endif
