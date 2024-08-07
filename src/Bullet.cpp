#include "Bullet.h"

Bullet::Bullet(float x, float y, float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
    entityRect = {static_cast<int>(x), static_cast<int>(y), 8, 8};
    angle = 0.0f;
}
