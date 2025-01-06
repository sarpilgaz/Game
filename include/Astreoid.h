#ifndef ASTREOID_H
#define ASTREOID_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include <vector>

class Astreoid : public Entity {

public:
    Astreoid(float x, float y, float vx, float vy, SDL_Renderer* renderer);
    void spinAstreoid();
    std::vector<SDL_Point> getSpriteVertices() const override;
private:
    float SPIN_SPEED = 0.016f;
};



#endif