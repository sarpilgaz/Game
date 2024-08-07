#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Bullet: public Entity {

public:
    Bullet(float x, float y, float vx, float vy);
    static constexpr float BULLET_SPEED = 6.0f;
};

#endif