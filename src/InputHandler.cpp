#include "InputHandler.h"

void InputHandler::handleEvents(bool& running) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        // Handle other inputs here
    }
}
