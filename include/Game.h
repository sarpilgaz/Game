#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <vector>
#include "Logger.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Player.h"
#include "Bullet.h"
#include "Engine.h"
#include "Astreoid.h"
class Game {
public:
    Game();
    ~Game();
    std::unordered_map<InputHandler::Keys, bool> keyStates = {
        {InputHandler::UP, false},
        {InputHandler::LEFT, false},
        {InputHandler::DOWN, false},
        {InputHandler::RIGHT, false},
        {InputHandler::A, false},
    };

    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Logger logger;
    Renderer gameRenderer;
    InputHandler inputHandler;
    Player player;
    Engine engine;
    vector<Astreoid> astreoidsUsed;
    vector<Astreoid> astreoidsNotUsed;
    vector<Bullet> bulletUsed;
    vector<Bullet> bulletNotUsed;
    
    bool running;
    const int ASTREOID_SPAWN_INTERVAL = 3000; // 3000 milliseconds = 3 seconds
    Uint32 lastAsteroidSpawnTime = 0;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    bool bulletShot = false;
};

#endif
