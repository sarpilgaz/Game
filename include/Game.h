#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "Logger.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Player.h"
class Game {
public:
    Game();
    ~Game();
    std::unordered_map<InputHandler::Keys, bool> keyStates = {
        {InputHandler::W, false},
        {InputHandler::A, false},
        {InputHandler::S, false},
        {InputHandler::D, false}
    };

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
