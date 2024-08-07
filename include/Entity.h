#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_image.h>

class Entity {
protected:
    float vx, vy;
    SDL_Texture* entityTex;

public:
    Entity() : vx(0), vy(0) {}
    SDL_Rect entityRect;

    int getVx() const { return vx; }
    int getVy() const { return vy; }
    SDL_Texture* getTex() const { return entityTex; }


    void setVx(int newVx) { vx = newVx; }
    void setVy(int newVy) { vy = newVy; }
    void setTex(SDL_Texture* tex) { entityTex = tex; }
    void updateVx(float amount);
    void updateVy(float amount);
    void updatePos();
};

#endif // ENTITY_H