#include "Astreoid.h"

Astreoid::Astreoid(float x, float y, float vx, float vy, SDL_Renderer* renderer) {
    this->vx = vx;
    this->vy = vy;
    angle = 0.0f;
    entityRect = {static_cast<int>(x), static_cast<int>(y), 64, 64};
    SDL_Surface* tmpSurf = IMG_Load("assets/sprites/Sprite-0002.png");
    setTex(SDL_CreateTextureFromSurface(renderer, tmpSurf));
    SDL_FreeSurface(tmpSurf);
}

void Astreoid::spinAstreoid() {
    angle += SPIN_SPEED;
    if (angle < 0) {
        angle += 2 * M_PI;
    } else if (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
    }
}