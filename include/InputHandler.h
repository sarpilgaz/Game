#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <unordered_map>

class InputHandler {
public:
    enum Keys {
        W,
        A,
        S,
        D,
        Z
    };
    void handleEvents(bool& running, std::unordered_map<Keys, bool>& keystates);

private:
    SDL_Event event;
};

#endif
