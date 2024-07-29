#include "Game.h"

Game::Game() : running(false), window(nullptr), renderer(nullptr), logger("logs.txt") {}

const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

vector<Bullet> used;
vector<Bullet> notUsed;
bool bulletShot = false;

Game::~Game() {
    clean();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    gameRenderer.setRenderer(renderer);

    SDL_Surface* tmpSurface = IMG_Load("assets/sprites/Sprite-0001.png");
    player.setTex(SDL_CreateTextureFromSurface(renderer, tmpSurface));
    SDL_FreeSurface(tmpSurface);

    running = true;
    return true;
}

void Game::run() {
    while (running) {
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        } 
    }
}

void Game::handleEvents() {
    inputHandler.handleEvents(running, keyStates);
}

void Game::update() {
    engine.updatePlayerPosition(keyStates, player);

    engine.handleShooting(keyStates, player, used, notUsed);

    engine.updateBulletPositions(used, notUsed);
}

void Game::render() {
    gameRenderer.render(player, used);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
