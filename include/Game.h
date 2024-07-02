#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Logger.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Player.h"
class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Logger logger;
    Renderer gameRenderer;
    InputHandler inputHandler;
    Player player;
};

#endif
