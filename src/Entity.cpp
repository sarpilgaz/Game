#include "Entity.h"

void Entity::updateVx(float amount) {
    vx = vx + amount;
}

void Entity::updateVy(float amount) {
    vy = vy + amount;
}

void Entity::updatePos() {
    entityRect.x += vx;
    entityRect.y += vy;
}

std::array<SDL_Point, 4> Entity::getVertices() const {
    std::array<SDL_Point, 4> vertices;
    float cosA = cos(angle * M_PI / 180.0);
    float sinA = sin(angle * M_PI / 180.0);

    float halfW = entityRect.w / 2;
    float halfH = entityRect.h / 2;

    vertices[0] = { static_cast<int>(entityRect.x + halfW * cosA - halfH * sinA), static_cast<int>(entityRect.y + halfW * sinA + halfH * cosA) };
    vertices[1] = { static_cast<int>(entityRect.x + halfW * cosA + halfH * sinA), static_cast<int>(entityRect.y + halfW * sinA - halfH * cosA) };
    vertices[2] = { static_cast<int>(entityRect.x - halfW * cosA + halfH * sinA), static_cast<int>(entityRect.y - halfW * sinA - halfH * cosA) };
    vertices[3] = { static_cast<int>(entityRect.x - halfW * cosA - halfH * sinA), static_cast<int>(entityRect.y - halfW * sinA + halfH * cosA) };

    return vertices;
}