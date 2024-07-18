#include "Game.h"

Game::Game() : running(false), window(nullptr), renderer(nullptr), logger("logs.txt") {}

const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

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

vector<Bullet> used;
vector<Bullet> notUsed;

void Game::update() {
    float tipX;
    float tipY;


    if (keyStates[InputHandler::D]) {
        if (player.getVx() < 3) {
            player.updateVx(0.4f);
        }
    }
    if (keyStates[InputHandler::A]) {
        if (player.getVx() > -3) {
            player.updateVx(-0.4f);
        }
    }
    if (keyStates[InputHandler::S]) {
        if (player.getVy() < 3) {
            player.updateVy(0.4f);
        }
    }
    if (keyStates[InputHandler::W]) {
        if (player.getVy() > -3) {
            player.updateVy(-0.4f);
        }
    }

    player.updatePos();
    player.getTipCoord(tipX, tipY);

    if (keyStates[InputHandler::Z]) {
        if (notUsed.size() == 0) {
            Bullet b(tipX, tipY);
            used.push_back(b);
        }
        else if (notUsed.size() > 0) {
            Bullet b = notUsed.back();
            notUsed.pop_back();
            b.bulletRect.x = tipX;
            b.bulletRect.y = tipY;
            used.push_back(b);
        }
    }

    for (auto& b : used) {
        b.updatePos(player.getVx(), player.getVy());
    }

}

void Game::render() {
    gameRenderer.render(player, used);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
