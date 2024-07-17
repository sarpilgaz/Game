#include "Renderer.h"
#include "Player.h"

void Renderer::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Renderer::render(const Player& player) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //SDL_RenderCopy(renderer, player.getTex(), NULL, &player.playerCharacter);
    SDL_RenderCopyEx(renderer, player.getTex(), NULL, &player.playerCharacter, player.angle * (180.0 / M_PI), nullptr, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}
