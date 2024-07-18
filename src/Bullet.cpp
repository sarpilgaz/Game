#include "Bullet.h"

Bullet::Bullet(float x, float y) {
    vx = 1.0f;
    vy = 1.0f;
    bulletRect = {static_cast<int>(x), static_cast<int>(y), 8, 8};
}

void Bullet::updatePos(float playerVx, float playerVy) {
    bulletRect.x = bulletRect.x + vx;
    bulletRect.y = bulletRect.y + vy;
}