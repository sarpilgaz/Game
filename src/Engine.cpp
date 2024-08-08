#include "Engine.h"

void Engine::updateGamestate(std::unordered_map<InputHandler::Keys, bool>& keystates, 
                            Player& player,
                            std::vector<Bullet>& bulletsUsed,
                            std::vector<Bullet>& bulletsNotUsed,
                            std::vector<Astreoid>& astreoidsUsed,
                            std::vector<Astreoid>& astreoidsNotUsed,
                            SDL_Renderer* renderer) 
    {
        updatePlayerPosition(keystates, player);

        handleShooting(keystates, player, bulletsUsed, bulletsNotUsed);

        updateBulletPositions(bulletsUsed, bulletsNotUsed);

        if(keystates[InputHandler::U]) {
            spawnAstreoidRandomly(astreoidsUsed, astreoidsNotUsed, renderer);
        }

        updateAstreoidPositions(astreoidsUsed, astreoidsNotUsed);    

        for (auto& ast : astreoidsUsed) {
            for (auto& bul : bulletsUsed) {
                if (checkCircularCollision(ast, bul)) {
                    std::cout << "collision" << std::endl;
                } else std::cout << "no collision" << std::endl; 
            }
        }                  
    }


void Engine::spawnAstreoid(std::vector<Astreoid>& astreoidsUsed, std::vector<Astreoid>& astreoidsUnUsed, SDL_Renderer* renderer) {
    spawnAstreoidRandomly(astreoidsUsed, astreoidsUnUsed, renderer);
}

// Generate a random float between min and max
float Engine::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Engine::calculateRandomAstreoidVelocity(Astreoid& astreoid, float targetX, float targetY) {
    //determine direction vector & normalize vector
    float dx = targetX - astreoid.entityRect.x;
    float dy = targetY - astreoid.entityRect.y;
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
            float bulletVx = (Bullet::BULLET_SPEED + abs(player.getVx())) * cos(player.getAngle() - M_PI_2);
            float bulletVy = (Bullet::BULLET_SPEED + abs(player.getVy())) * sin(player.getAngle() - M_PI_2); 
            if (notUsed.empty()) {
                Bullet b(tipX, tipY, bulletVx, bulletVy);
                used.push_back(b);
            }
            else {
                Bullet b = std::move(notUsed.back());
                notUsed.pop_back();
                b.entityRect.x = static_cast<int>(tipX);
                b.entityRect.y = static_cast<int>(tipY);
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
        if (it->entityRect.x > SCREEN_WIDTH || it->entityRect.y > SCREEN_HEIGHT || it->entityRect.x < 0 || it->entityRect.y < 0) {
            notUsed.push_back(*it);
            it = used.erase(it); // Erase and update the iterator
        } else {
            ++it; // Move to the next element
        }
    }
}

void Engine::updateAstreoidPositions(std::vector<Astreoid>& used, std::vector<Astreoid>& notUsed) {
    for (auto it = used.begin(); it != used.end();) {
        it->updatePos();
        it->spinAstreoid();
        if (it->entityRect.x > SCREEN_WIDTH + 200 || it->entityRect.y > SCREEN_HEIGHT + 200 || it->entityRect.x < -200 || it->entityRect.y < -200) {
            notUsed.push_back(*it);
            it = used.erase(it);
        } else {
            it++;
        }
    }
}

void Engine::spawnAstreoidRandomly(std::vector<Astreoid>& astreoidsUsed, std::vector<Astreoid>& astreoidsUnUsed, SDL_Renderer* renderer) {

    Astreoid ast = astreoidsUnUsed.empty() ? Astreoid(renderer) : std::move(astreoidsUnUsed.back());
    int side = rand() % 4;

    switch(side) {
        case 0: //top
            ast.entityRect.x = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET);
            ast.entityRect.y = -ASTREOID_SPAWN_OFFSET;
            calculateRandomAstreoidVelocity(ast, randomFloat(0, SCREEN_WIDTH), SCREEN_HEIGHT / 2);
            break;
        case 1: //right
            ast.entityRect.x = SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET;
            ast.entityRect.y = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_HEIGHT+ ASTREOID_SPAWN_OFFSET);
            calculateRandomAstreoidVelocity(ast, 0, randomFloat(0, SCREEN_HEIGHT));
            break;
        case 2: //bottom
            ast.entityRect.x = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET);
            ast.entityRect.y = SCREEN_HEIGHT +ASTREOID_SPAWN_OFFSET;
            calculateRandomAstreoidVelocity(ast, randomFloat(0, SCREEN_WIDTH), 0);
            break;
        case 3: //left
            ast.entityRect.x = -ASTREOID_SPAWN_OFFSET;
            ast.entityRect.y = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_HEIGHT + ASTREOID_SPAWN_OFFSET);
            calculateRandomAstreoidVelocity(ast, SCREEN_WIDTH, randomFloat(0, SCREEN_HEIGHT)); 
            break;       
    }

    if (!astreoidsUnUsed.empty()) {
        astreoidsUnUsed.pop_back();
    }

    astreoidsUsed.push_back(ast);

}

bool Engine::checkCircularCollision(const Entity& circleEntity, const Entity& rectEntity) {
    float circleCenterX = circleEntity.entityRect.x + circleEntity.entityRect.w/2;
    float circleCenterY = circleEntity.entityRect.y + circleEntity.entityRect.h/2;
    float radius = circleEntity.entityRect.w/2; // astreoids are squares

    float closestX = std::max(rectEntity.entityRect.x, std::min(static_cast<int> (circleCenterX), rectEntity.entityRect.x + rectEntity.entityRect.w));
    float closestY = std::max(rectEntity.entityRect.y, std::min(static_cast<int>(circleCenterY), rectEntity.entityRect.y + rectEntity.entityRect.h));

    // Calculate the distance between the circle's center and this closest point
    float distanceX = circleCenterX - closestX;
    float distanceY = circleCenterY - closestY;

    // If the distance is less than the circle's radius, there's an intersection
    return (distanceX * distanceX + distanceY * distanceY) < (radius * radius);
}

bool Engine::checkCollisionsSAT(const Entity& e1, const Entity& e2) {
    auto vertices1 = e1.getVertices();
    auto vertices2 = e2.getVertices();

    // Create an array to store the axes for both entities
    std::array<SDL_Point, 8> axes = {
        // For the first rectangle (e1)
        SDL_Point{vertices1[1].y - vertices1[0].y, vertices1[0].x - vertices1[1].x}, // Perpendicular to edge (0 to 1)
        SDL_Point{vertices1[2].y - vertices1[1].y, vertices1[1].x - vertices1[2].x}, // Perpendicular to edge (1 to 2)
        SDL_Point{vertices1[3].y - vertices1[2].y, vertices1[2].x - vertices1[3].x}, // Perpendicular to edge (2 to 3)
        SDL_Point{vertices1[0].y - vertices1[3].y, vertices1[3].x - vertices1[0].x}, // Perpendicular to edge (3 to 0)

        // For the second rectangle (e2)
        SDL_Point{vertices2[1].y - vertices2[0].y, vertices2[0].x - vertices2[1].x}, // Perpendicular to edge (0 to 1)
        SDL_Point{vertices2[2].y - vertices2[1].y, vertices2[1].x - vertices2[2].x}, // Perpendicular to edge (1 to 2)
        SDL_Point{vertices2[3].y - vertices2[2].y, vertices2[2].x - vertices2[3].x}, // Perpendicular to edge (2 to 3)
        SDL_Point{vertices2[0].y - vertices2[3].y, vertices2[3].x - vertices2[0].x}  // Perpendicular to edge (3 to 0)
    };

    // Iterate through all axes
    for (auto& axis : axes) {
        // Normalize the axis
        float length = sqrt(axis.x * axis.x + axis.y * axis.y);
        if (length != 0) { 
            axis.x /= length;
            axis.y /= length;
        }

        float min1, max1, min2, max2;
        // Project vertices of both rectangles onto the current axis
        projectOntoAxis(vertices1, axis, min1, max1);
        projectOntoAxis(vertices2, axis, min2, max2);

        // Check for a separating axis
        if (max1 < min2 || max2 < min1) {
            return false; // No collision
        }
    }
    return true; // Collision detected
}

void Engine::projectOntoAxis(const std::array<SDL_Point, 4>& vertices, const SDL_Point& axis, float& min, float& max) {
    min = max = (vertices[0].x * axis.x + vertices[0].y * axis.y);
    for (const auto& vertex : vertices) {
        float projection = (vertex.x * axis.x + vertex.y * axis.y);
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }
}