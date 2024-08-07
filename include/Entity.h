#ifndef ENTITY_H
#define ENTITY_H

#include <SDL_image.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <array>

class Entity {
protected:
    float vx, vy;
    float angle;
    SDL_Texture* entityTex;


public:
    Entity() : vx(0), vy(0) {}
    SDL_Rect entityRect;
    std::array<SDL_Point, 4> getVertices() const;

    int getVx() const { return vx; }
    int getVy() const { return vy; }
    float getAngle() const { return angle; }
    SDL_Texture* getTex() const { return entityTex; }


    void setVx(int newVx) { vx = newVx; }
    void setVy(int newVy) { vy = newVy; }
    void setAngle(float newAngle) { angle = newAngle; }
    void setTex(SDL_Texture* tex) { entityTex = tex; }
    void updateVx(float amount);
    void updateVy(float amount);
    void updatePos();
};

#endif // ENTITY_H