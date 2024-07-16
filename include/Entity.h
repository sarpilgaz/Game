#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_image.h>

class Entity {
protected:
    int x, y;
    int vx, vy;

public:
    Entity() : x(0), y(0), vx(0), vy(0) {}
    SDL_Texture* entityTex;

    int getX() const { return x; }
    int getY() const { return y; }
    int getVx() const { return vx; }
    int getVy() const { return vy; }
    SDL_Texture* getTex() const { return entityTex; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setVx(int newVx) { vx = newVx; }
    void setVy(int newVy) { vy = newVy; }
    void setTex(SDL_Texture* tex) { entityTex = tex; }
};

#endif // ENTITY_H