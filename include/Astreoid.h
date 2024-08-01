#ifndef ASTREOID_H
#define ASTREOID_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Astreoid : public Entity {

public:
    Astreoid(SDL_Renderer* renderer);
    SDL_Rect astreoidRect;
    void spinAstreoid();
    float angle;
private:
    const float SPIN_SPEED = 0.016f;
};



#endif