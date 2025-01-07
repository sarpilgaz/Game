#include "InputHandler.h"
#include <iostream>
void InputHandler::handleEvents(bool& running, std::unordered_map<Keys, bool>& keystates) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            
        } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            bool isPressed = (event.type == SDL_KEYDOWN);
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    keystates[UP] = isPressed;
                    break;
                case SDLK_LEFT:
                    keystates[LEFT] = isPressed;
                    break;
                case SDLK_DOWN:
                    keystates[DOWN] = isPressed;
                    break;
                case SDLK_RIGHT:
                    keystates[RIGHT] = isPressed;
                    break;
                case SDLK_a:
                    keystates[A] = isPressed;
                    break;
                case SDLK_u:
                    keystates[U] = isPressed;
            }
        }
    }
}
void InputHandler::resetKeys(std::unordered_map<Keys, bool>& keystates) {
    keystates[UP] = false;
    keystates[LEFT] = false;
    keystates[DOWN] = false;
    keystates[RIGHT] = false;
    keystates[A] = false;
    keystates[U] = false;
}
