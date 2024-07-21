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
                    keystates[W] = isPressed;
                    break;
                case SDLK_LEFT:
                    keystates[A] = isPressed;
                    break;
                case SDLK_DOWN:
                    keystates[S] = isPressed;
                    break;
                case SDLK_RIGHT:
                    keystates[D] = isPressed;
                    break;
                case SDLK_a:
                    keystates[Z] = isPressed;
                    break;
            }
        }
        /*
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_z) {
                keystates[Z] = true;
            }
        } 
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_z) {
                keystates[Z] = false;
            }
        } */
    }
        std::cout << "Key states: W=" << keystates[W]
              << " A=" << keystates[A]
              << " S=" << keystates[S]
              << " D=" << keystates[D]
              << " Z=" << keystates[Z] << std::endl;

}
