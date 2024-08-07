#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Player : public Entity {
public:
    Player();

    int getHealth() const { return health; }
    void setHealth(int newHealth) { health = newHealth; }
    void updatePos();
    void getTipCoord(float& x, float& y);

private:
    int health;
    const float SHIP_LENGTH = 16.0f;
};

#endif // PLAYER_H