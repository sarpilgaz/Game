#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>

class InputHandler {
public:
    void handleEvents(bool& running);

private:
    SDL_Event event;
};

#endif
