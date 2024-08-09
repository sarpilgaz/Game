#include "Renderer.h"
#include "Player.h"
#include "Bullet.h"
#include "Astreoid.h"

void Renderer::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Renderer::render(const Player& player, std::list<Bullet>& activeBullets, std::list<Astreoid>& astreoids) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopyEx(renderer, player.getTex(), NULL, &player.entityRect, player.getAngle() * (180.0 / M_PI), nullptr, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (auto b : activeBullets) {
        SDL_RenderDrawRect(renderer, &b.entityRect);
    }

    for (auto a : astreoids) {
        SDL_RenderCopyEx(renderer, a.getTex(), NULL, &a.entityRect, a.getAngle() * (180.0 / M_PI), nullptr, SDL_FLIP_NONE);
    }

    SDL_RenderPresent(renderer);
}
