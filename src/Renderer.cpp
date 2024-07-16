#include "Renderer.h"
#include "Player.h"

void Renderer::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Renderer::render(const Player& player) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game objects here
    SDL_RenderCopy(renderer, player.getTex(), NULL, &player.playerCharacter);
    SDL_RenderPresent(renderer);
}
