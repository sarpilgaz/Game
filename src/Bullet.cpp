#include "Bullet.h"

Bullet::Bullet(float x, float y, float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
    bulletRect = {static_cast<int>(x), static_cast<int>(y), 8, 8};
}

void Bullet::updatePos() {
    bulletRect.x = bulletRect.x + vx;
    bulletRect.y = bulletRect.y + vy;
}