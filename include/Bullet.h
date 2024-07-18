#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Bullet: public Entity {

public:
    Bullet(float x, float y);
    SDL_Rect bulletRect;
    void updatePos(float playerVx, float playervy);



};

#endif