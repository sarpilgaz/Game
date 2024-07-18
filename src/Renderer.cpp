#include "Renderer.h"
#include "Player.h"
#include "Bullet.h"

void Renderer::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Renderer::render(const Player& player, std::vector<Bullet>& activeBullets) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopyEx(renderer, player.getTex(), NULL, &player.playerCharacter, player.angle * (180.0 / M_PI), nullptr, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (auto b : activeBullets) {
        SDL_RenderDrawRect(renderer, &b.bulletRect);
    }
    SDL_RenderPresent(renderer);
}
