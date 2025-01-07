#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <vector>
#include "Entity.h"

class Player : public Entity {
public:
    Player();

    int getHealth() const { return health; }
    void setHealth(int newHealth) { health = newHealth; }
    int getScore() const { return score; }
    void setScore(int newScore) { score = newScore; }

    void updatePos();
    void getTipCoord(float& x, float& y);
    std::vector<SDL_Point> getSpriteVertices() const override;

private:
    int health = 3;
    int score = 0;
    const float SHIP_LENGTH = 16.0f;
};

#endif // PLAYER_H