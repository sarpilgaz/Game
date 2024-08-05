#include "Engine.h"

// Generate a random float between min and max
float Engine::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Engine::calculateRandomAstreoidVelocity(Astreoid& astreoid, float targetX, float targetY) {
    //determine direction vector & normalize vector
    float dx = targetX - astreoid.astreoidRect.x;
    float dy = targetY - astreoid.astreoidRect.y;
    float length = std::sqrt(dx * dx + dy * dy);
    dx /= length;
    dy /= length;

    float velMagnitude = randomFloat(MIN_ASTREOID_VELOCITY, MAX_ASTREOID_VELOCITY);
    astreoid.setVx(dx * velMagnitude);
    astreoid.setVy(dy * velMagnitude);
}

void Engine::updatePlayerPosition(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player) {
    if (keyStates[InputHandler::RIGHT]) {
        if (player.getVx() < 3) {
            player.updateVx(0.4f);
        }
    }
    if (keyStates[InputHandler::LEFT]) {
        if (player.getVx() > -3) {
            player.updateVx(-0.4f);
        }
    }
    if (keyStates[InputHandler::DOWN]) {
        if (player.getVy() < 3) {
            player.updateVy(0.4f);
        }
    }
    if (keyStates[InputHandler::UP]) {
        if (player.getVy() > -3) {
            player.updateVy(-0.4f);
        }
    }

    player.updatePos();

}

void Engine::handleShooting(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player, std::vector<Bullet>& used, std::vector<Bullet>& notUsed) {
    float tipX;
    float tipY;
    player.getTipCoord(tipX, tipY);

    if (keyStates[InputHandler::A]) {
        if (!bulletShot) {
            float bulletVx = (Bullet::BULLET_SPEED + abs(player.getVx())) * cos(player.angle - M_PI_2);
            float bulletVy = (Bullet::BULLET_SPEED + abs(player.getVy())) * sin(player.angle - M_PI_2); 
            if (notUsed.empty()) {
                Bullet b(tipX, tipY, bulletVx, bulletVy);
                used.push_back(b);
            }
            else {
                Bullet b = notUsed.back();
                notUsed.pop_back();
                b.bulletRect.x = static_cast<int>(tipX);
                b.bulletRect.y = static_cast<int>(tipY);
                b.setVx(bulletVx);
                b.setVy(bulletVy);
                used.push_back(b);
            }
        }    
        bulletShot = true;
    }
    if (!keyStates[InputHandler::A]) {
        bulletShot = false;
    }
}

void Engine::updateBulletPositions(std::vector<Bullet>& used, std::vector<Bullet>& notUsed) {
    for (auto it = used.begin(); it != used.end(); ) {
        it->updatePos();
        if (it->bulletRect.x > SCREEN_WIDTH || it->bulletRect.y > SCREEN_HEIGHT || it->bulletRect.x < 0 || it->bulletRect.y < 0) {
            notUsed.push_back(*it);
            it = used.erase(it); // Erase and update the iterator
        } else {
            ++it; // Move to the next element
        }
    }
}

void Engine::updateAstreoidPositions(std::vector<Astreoid>& astreoids) {
    for (auto& ast : astreoids) {
        ast.updatePos();
        ast.spinAstreoid();
    }
}

void Engine::SpawnAstreoidRandomly(std::vector<Astreoid>& astreoids, SDL_Renderer* renderer) {
    Astreoid ast(renderer);

    int side = rand() % 4;

    switch(side) {
        case 0: //top
            ast.astreoidRect.x = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET);
            ast.astreoidRect.y = -ASTREOID_SPAWN_OFFSET;
            calculateRandomAstreoidVelocity(ast, randomFloat(0, SCREEN_WIDTH), SCREEN_HEIGHT / 2);
            break;
        case 1: //right
            ast.astreoidRect.x = SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET;
            ast.astreoidRect.y = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_HEIGHT+ ASTREOID_SPAWN_OFFSET);
            calculateRandomAstreoidVelocity(ast, 0, randomFloat(0, SCREEN_HEIGHT));
            break;
        case 2: //bottom
            ast.astreoidRect.x = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET);
            ast.astreoidRect.y = SCREEN_HEIGHT +ASTREOID_SPAWN_OFFSET;
            calculateRandomAstreoidVelocity(ast, randomFloat(0, SCREEN_WIDTH), 0);
            break;
        case 3: //left
            ast.astreoidRect.x = -ASTREOID_SPAWN_OFFSET;
            ast.astreoidRect.y = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_HEIGHT + ASTREOID_SPAWN_OFFSET);
            calculateRandomAstreoidVelocity(ast, SCREEN_WIDTH, randomFloat(0, SCREEN_HEIGHT)); 
            break;       
    }

    astreoids.push_back(ast);

}