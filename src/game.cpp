#include "Game.h"
#include "Logger.h"

Logger logger("logs.txt");

Game::Game() {
    window = nullptr;
    renderer = nullptr;
    running = false;
}

Game::~Game() {}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
    }
    logger.log(DEBUG, "hey do you work??");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    running = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void Game::update() {}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render here

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    logger.log(DEBUG, "BYE BYE");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    logger.~Logger();
    SDL_Quit();
}

bool Game::isRunning() {
    return running;
}