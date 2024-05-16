#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
public:
    Game();
    ~Game();

    bool init();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
};

#endif // GAME_H