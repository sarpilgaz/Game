#include "Player.h"
#include <cmath>

Player::Player(){  
    vx = 0.0f;
    vy = 0.0f;
    angle = 0.0f; 
    entityRect = {150, 150, 32, 32};
    health = 3;
}

void Player::updatePos() {
    entityRect.x += vx;
    entityRect.y += vy;

    float targetAngle = atan2(vy, vx) + M_PI_2;
    float rotationSpeed = 0.04f;
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
    float centerX = entityRect.x + entityRect.w / 2;
    float centerY = entityRect.y + entityRect.h / 2;

    const float OFFSET = 5.0f;

    float tipX = centerX + (SHIP_LENGTH + OFFSET) * cos(angle - M_PI_2);
    float tipY = centerY + (SHIP_LENGTH + OFFSET) * sin(angle - M_PI_2);

    // Final position accounting for bullet sprite size dynamically (centered bullets)
    const float BULLET_SIZE = 8.0f; // Example bullet size
    x = tipX - BULLET_SIZE / 2;
    y = tipY - BULLET_SIZE / 2;
}

std::vector<SDL_Point> Player::getSpriteVertices() const {
    float centerX = entityRect.x + entityRect.w / 2;
    float centerY = entityRect.y + entityRect.h / 2;

    SDL_Point tip = {centerX + SHIP_LENGTH * cos(angle - M_PI_2), centerY + SHIP_LENGTH * sin(angle - M_PI_2) };

    SDL_Point leftBase = {centerX + entityRect.w * cos(angle + M_PI_2 * 2 / 3), centerY + entityRect.w * sin(angle + M_PI_2 * 2 / 3)};

    SDL_Point rightBase = {centerX + entityRect.w * cos(angle - M_PI_2 * 2 / 3), centerY + entityRect.w * sin(angle - M_PI_2 * 2 / 3)};

    return {tip, leftBase, rightBase};
}