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

std::array<SDL_Point, 4> Entity::getRectVertices() const {
    std::array<SDL_Point, 4> vertices;
    float cosA = cos(angle * M_PI / 180.0);
    float sinA = sin(angle * M_PI / 180.0);

    float halfW = entityRect.w / 2.0f;
    float halfH = entityRect.h / 2.0f;

    float centerX = entityRect.x + halfW;
    float centerY = entityRect.y + halfH;

    // Top-left corner
    vertices[0] = { static_cast<int>(centerX + (-halfW * cosA - -halfH * sinA)), static_cast<int>(centerY + (-halfW * sinA + -halfH * cosA)) };
    // Top-right corner
    vertices[1] = { static_cast<int>(centerX + (halfW * cosA - -halfH * sinA)), static_cast<int>(centerY + (halfW * sinA + -halfH * cosA)) };
    // Bottom-right corner
    vertices[2] = { static_cast<int>(centerX + (halfW * cosA - halfH * sinA)), static_cast<int>(centerY + (halfW * sinA + halfH * cosA)) };
    // Bottom-left corner
    vertices[3] = { static_cast<int>(centerX + (-halfW * cosA - halfH * sinA)), static_cast<int>(centerY + (-halfW * sinA + halfH * cosA)) };

    return vertices;
}
