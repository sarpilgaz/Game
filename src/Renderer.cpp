#include "Renderer.h"
#include "Player.h"
#include "Bullet.h"
#include "Astreoid.h"

void Renderer::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Renderer::render(const Player& player, std::list<Bullet>& activeBullets, std::list<Astreoid>& astreoids) {
    switch(stateManager.getState()) {
        case GameState::Menu:
            renderMenu();
            break;
        case GameState::Start:
            renderGame(player, activeBullets, astreoids);
            break;
        case GameState::End:
            renderGameOver(player);
            break;
    }
}

void Renderer::prepareRender() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::renderText(const char* text, int xPos, int yPos) {
    // Initialize TTF if not already done
    // Load font
    TTF_Font* sans = TTF_OpenFont("fonts/sans.ttf", 24);
    if (!sans) {
        return;
    }

    // Render text
    SDL_Color white = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, text, white);
    if (!surfaceMessage) {
        TTF_CloseFont(sans);
        return;
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        SDL_FreeSurface(surfaceMessage);
        TTF_CloseFont(sans);
        return;
    }

    // Set dynamic dimensions
    SDL_Rect msgRect = {xPos, yPos, surfaceMessage->w, surfaceMessage->h};

    // Copy text texture and present renderer
    SDL_RenderCopy(renderer, message, NULL, &msgRect);

    // Cleanup
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
    TTF_CloseFont(sans);
}

void Renderer::renderMenu() {
    prepareRender();
    std::string msg_str = "Press A to start";
    renderText(msg_str.c_str(), 300, 200);
    SDL_RenderPresent(renderer);
}
void Renderer::renderGame(const Player& player, std::list<Bullet>& activeBullets, std::list<Astreoid>& astreoids) {
    prepareRender();

    SDL_RenderCopyEx(renderer, player.getTex(), NULL, &player.entityRect, player.getAngle() * (180.0 / M_PI), nullptr, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (auto b : activeBullets) {
        SDL_RenderDrawRect(renderer, &b.entityRect);
    }

    for (auto a : astreoids) {
        SDL_RenderCopyEx(renderer, a.getTex(), NULL, &a.entityRect, a.getAngle() * (180.0 / M_PI), nullptr, SDL_FLIP_NONE);
    }

    std::string healthStr = std::to_string(player.getHealth());
    std::string healthText = "Lives: " + healthStr;

    renderText(healthText.c_str(), 1, 0);


    std::string scoreStr = std::to_string(player.getScore());
    std::string scoreText = "Score: " + scoreStr;

    renderText(scoreText.c_str(), 680, 0);

    SDL_RenderPresent(renderer);
}

void Renderer::renderGameOver(const Player& player) {
    prepareRender();
    std::string msg_str = "Game Over!";
    renderText(msg_str.c_str(), 300, 200);
    std::string scoreStr = std::to_string(player.getScore());
    std::string scoreMsg = "Score: " + scoreStr;
    renderText(scoreMsg.c_str(), 300, 250);
    SDL_RenderPresent(renderer);
}