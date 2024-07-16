#include "Player.h"

Player::Player(){  
    x = 150;
    y = 150;
    width = 32;
    height = 32;
    vx = 0;
    vy = 0; 
    playerCharacter = {x, y, width, height};
    health = 100;
}