#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_image.h>

class Entity {
protected:
    int vx, vy;

public:
    Entity() : vx(0), vy(0) {}
    SDL_Texture* entityTex;

    int getVx() const { return vx; }
    int getVy() const { return vy; }
    SDL_Texture* getTex() const { return entityTex; }


    void setVx(int newVx) { vx = newVx; }
    void setVy(int newVy) { vy = newVy; }
    void setTex(SDL_Texture* tex) { entityTex = tex; }
    void updateVx(int amount);
    void updateVy(int amount);
};

#endif // ENTITY_H