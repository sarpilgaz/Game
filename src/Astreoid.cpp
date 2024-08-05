#include "Astreoid.h"

Astreoid::Astreoid(SDL_Renderer* renderer) {
    angle = 0.0f;
    astreoidRect = {200, 200, 64, 64};
    SDL_Surface* tmpSurf = IMG_Load("assets/sprites/Sprite-0002.png");
    setTex(SDL_CreateTextureFromSurface(renderer, tmpSurf));
    SDL_FreeSurface(tmpSurf);
}

void Astreoid::spinAstreoid() {
    angle += Astreoid::SPIN_SPEED;
    if (angle < 0) {
        angle += 2 * M_PI;
    } else if (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
    }
}

void Astreoid::updatePos() {
    astreoidRect.x += getVx();
    astreoidRect.y += getVy();
}