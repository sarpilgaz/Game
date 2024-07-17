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

private:
    int health;
};

#endif // PLAYER_H