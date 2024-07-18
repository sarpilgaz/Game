#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Player : public Entity {
public:
    Player();
    SDL_Rect playerCharacter;
    float angle;

    int getHealth() const { return health; }
    void setHealth(int newHealth) { health = newHealth; }
    void updatePos();
    void getTipCoord(float& x, float& y);

private:
    int health;
    const float SHIP_LENGTH = 32;
};

#endif // PLAYER_H