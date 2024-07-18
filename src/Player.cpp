#include "Player.h"
#include <cmath>

Player::Player(){  
    vx = 0.0f;
    vy = 0.0f;
    angle = 0.0f; 
    playerCharacter = {150, 150, 32, 32};
    health = 100;
}

void Player::updatePos() {
    playerCharacter.x = playerCharacter.x + vx;
    playerCharacter.y = playerCharacter.y + vy;

    float targetAngle = atan2(vy, vx) + M_PI_2;
    float rotationSpeed = 0.08f;
    float deltaAngle = targetAngle - angle;
    if (deltaAngle > M_PI) deltaAngle -= 2 * M_PI;
    if (deltaAngle < -M_PI) deltaAngle += 2 * M_PI;

    angle += deltaAngle * rotationSpeed;

    if (angle < 0) {
        angle += 2 * M_PI;
    } else if (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
    }

}

void Player::getTipCoord(float& x, float& y) {
    x = playerCharacter.x + SHIP_LENGTH * cos (angle - M_PI_2);
    y = playerCharacter.y + SHIP_LENGTH * sin (angle - M_PI_2);
}