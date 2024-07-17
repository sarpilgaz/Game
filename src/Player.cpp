#include "Player.h"

Player::Player(){  
    vx = 0;
    vy = 0; 
    playerCharacter = {150, 150, 32, 32};
    health = 100;
}

void Player::updatePos() {
    playerCharacter.x = playerCharacter.x + vx;
    playerCharacter.y = playerCharacter.y + vy;
}