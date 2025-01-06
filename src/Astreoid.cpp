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

std::vector<SDL_Point> Astreoid::getSpriteVertices() const {
    std::vector<SDL_Point> vertices;
    float centerX = entityRect.x + entityRect.w / 2;
    float centerY = entityRect.y + entityRect.h / 2;
    float radius = entityRect.w / 2;
    int segments = 16;


    const float angleStep = 2 * M_PI / segments; // Divide the circle into segments
    for (int i = 0; i < segments; ++i) {
        float angle = i * angleStep;
        vertices.push_back({
            static_cast<int>(centerX + radius * cos(angle)),
            static_cast<int>(centerY + radius * sin(angle))
        });
    }
    return vertices;
}