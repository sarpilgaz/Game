#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Player : public Entity {
public:
    Player();

    int getHealth() const { return health; }
    void setHealth(int newHealth) { health = newHealth; }

private:
    SDL_Rect playerCharacter;
    int width, height;
    int health;
};

#endif // PLAYER_H