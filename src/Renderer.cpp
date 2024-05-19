#include "Renderer.h"

void Renderer::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Renderer::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game objects here

    SDL_RenderPresent(renderer);
}
