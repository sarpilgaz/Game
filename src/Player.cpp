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
    // Center of the ship
    float centerX = playerCharacter.x + playerCharacter.w / 2;
    float centerY = playerCharacter.y + playerCharacter.h / 2;

    const float OFFSET = 5.0f;

    // Calculate the tip coordinates using the center as the origin
    x = centerX + (SHIP_LENGTH + OFFSET) * cos(angle - M_PI_2) - 4;
    y = centerY + (SHIP_LENGTH + OFFSET) * sin(angle - M_PI_2) - 4;
}