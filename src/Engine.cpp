#include "Engine.h"

void Engine::updateGamestate(std::unordered_map<InputHandler::Keys, bool>& keystates, 
                            Player& player,
                            std::list<Bullet>& bulletsUsed,
                            std::list<Bullet>& bulletsNotUsed,
                            std::list<Astreoid>& astreoidsUsed,
                            std::list<Astreoid>& astreoidsNotUsed,
                            bool spawnAstreoid,
                            SDL_Renderer* renderer) 
    {
        updatePlayerPosition(keystates, player);

        handleShooting(keystates, player, bulletsUsed, bulletsNotUsed);

        updateBulletPositions(bulletsUsed, bulletsNotUsed);

        //extra, for testing purposes
        if(keystates[InputHandler::U]) {
            spawnAstreoidRandomly(astreoidsUsed, astreoidsNotUsed, renderer);
        }

        updateAstreoidPositions(astreoidsUsed, astreoidsNotUsed);   

        handleBulletAstreoidCollision(bulletsUsed, bulletsNotUsed, astreoidsUsed, astreoidsNotUsed);

        //spawn astreoids after everything else?
        if (spawnAstreoid) {
            spawnAstreoidRandomly(astreoidsUsed, astreoidsNotUsed, renderer);
        }

    }


// Generate a random float between min and max
float Engine::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Engine::calculateRandomAstreoidVelocity(float& velX, float& velY, float x, float y, float targetX, float targetY) {
    float dx = targetX - x;
    float dy = targetY - y;
    float length = std::sqrt(dx * dx + dy * dy);
    dx /= length;
    dy /= length;

    float velMagnitude = randomFloat(MIN_ASTREOID_VELOCITY, MAX_ASTREOID_VELOCITY);
    velX = dx * velMagnitude;
    velY = dy * velMagnitude;
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
    int boundcheck = checkPlayerOutofBounds(player);
    switch (boundcheck) {
        case 0:
            player.entityRect.y = SCREEN_HEIGHT + 10;
            break;
        case 1:
            player.entityRect.y = -10;
            break;
        case 2:
            player.entityRect.x = SCREEN_WIDTH + 10;
            break;
        case 3:
            player.entityRect.x = -15;
            break;
    }

}

int Engine::checkPlayerOutofBounds(const Player& player) {
    /*
    returns which side the player went out of bound from, as:
        0 for top, 1 for bottom, 2 for left and 3 for right.
        -1 for inbounds  
    */
    std::array<SDL_Point, 4> vertices = player.getVertices();
    float maxX, maxY = std::numeric_limits<float>::lowest();
    /*
    because of arcane reasons beyond my mortal comprehension, if the following two initilizations are made in a single line, minX will be 
    incorrectly assigned a value of 0.04, but minY will be correctly initialized.

    Since having a debate with god, a.k.a the gnu c++ compiler, is futile and will surely lead to my decent into madness, I will instead leave this message 
    for my future self, or whoever is unfortunate enough to stumble here:

    DO NOT change the following 2 lines. DO NOT question them. DO NOT anger the c++ deities.
    */
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();

    for (auto& v : vertices) {
        if (v.x > maxX) maxX = v.x;
        if (v.x < minX) {minX = v.x;} 

        if (v.y > maxY) maxY = v.y;
        if (v.y < minY) minY = v.y;
    }

    if (maxY <= -15) return 0;
    else if (minY >= SCREEN_HEIGHT + 15) return 1;
    else if (maxX <= 0.5) return 2;
    else if (minX >= SCREEN_WIDTH + 15) return 3;
    else return -1;
}

void Engine::handleShooting(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player, std::list<Bullet>& used, std::list<Bullet>& notUsed) {
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

void Engine::updateBulletPositions(std::list<Bullet>& used, std::list<Bullet>& notUsed) {
    for (auto it = used.begin(); it != used.end(); ) {
        it->updatePos();
        if (it->entityRect.x > SCREEN_WIDTH || it->entityRect.y > SCREEN_HEIGHT || it->entityRect.x < 0 || it->entityRect.y < 0) {
            notUsed.push_back(*it);
            it = used.erase(it);
        } else {
            ++it; // Move to the next element
        }
    }
}

void Engine::updateAstreoidPositions(std::list<Astreoid>& used, std::list<Astreoid>& notUsed) {
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

void Engine::spawnAstreoidRandomly(std::list<Astreoid>& astreoidsUsed, std::list<Astreoid>& astreoidsUnused, SDL_Renderer* renderer) {

    float astX, astY, astVx, astVy;
    //Astreoid ast = astreoidsUnused.empty() ? Astreoid(renderer) : std::move(astreoidsUnused.back());
    int side = rand() % 4;

    switch(side) {
        case 0: //top
            astX = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET);
            astY = -ASTREOID_SPAWN_OFFSET;
            calculateRandomAstreoidVelocity(astVx, astVy, astX, astY,  randomFloat(0, SCREEN_WIDTH), SCREEN_HEIGHT / 2);
            break;
        case 1: //right
            astX = SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET;
            astY = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_HEIGHT+ ASTREOID_SPAWN_OFFSET);
            calculateRandomAstreoidVelocity(astVx, astVy, astX, astY, 0, randomFloat(0, SCREEN_HEIGHT));
            break;
        case 2: //bottom
            astX= randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_WIDTH + ASTREOID_SPAWN_OFFSET);
            astY = SCREEN_HEIGHT +ASTREOID_SPAWN_OFFSET;
            calculateRandomAstreoidVelocity(astVx, astVy, astX, astY, randomFloat(0, SCREEN_WIDTH), 0);
            break;
        case 3: //left
            astX = -ASTREOID_SPAWN_OFFSET;
            astY = randomFloat(-ASTREOID_SPAWN_OFFSET, SCREEN_HEIGHT + ASTREOID_SPAWN_OFFSET);
            calculateRandomAstreoidVelocity(astVx, astVy, astX, astY, SCREEN_WIDTH, randomFloat(0, SCREEN_HEIGHT)); 
            break;       
    }

    if (astreoidsUnused.empty()) {
        Astreoid ast(astX, astY, astVx, astVy, renderer);
        astreoidsUsed.push_back(ast);
    }
    else {
        Astreoid ast = std::move(astreoidsUnused.back());
        astreoidsUnused.pop_back();
        ast.entityRect.x = astX;
        ast.entityRect.y = astY;
        ast.setVx(astVx);
        ast.setVy(astVy);
        astreoidsUsed.push_back(ast);
    }
}

bool Engine::checkCircRectCollision(const Entity& circleEntity, const Entity& rectEntity) {
    float circleCenterX = circleEntity.entityRect.x + circleEntity.entityRect.w/2;
    float circleCenterY = circleEntity.entityRect.y + circleEntity.entityRect.h/2;
    float radius = circleEntity.entityRect.w/2; // astreoid rectangles are squares

    float closestX = std::max(rectEntity.entityRect.x, std::min(static_cast<int> (circleCenterX), rectEntity.entityRect.x + rectEntity.entityRect.w));
    float closestY = std::max(rectEntity.entityRect.y, std::min(static_cast<int>(circleCenterY), rectEntity.entityRect.y + rectEntity.entityRect.h));

    // Calculate the distance between the circle's center and this closest point
    float distanceX = circleCenterX - closestX;
    float distanceY = circleCenterY - closestY;

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

bool Engine::checkCircCircCollision(const Entity& e1, const Entity& e2) {
    float xe1 = e1.entityRect.x + e1.entityRect.w/2;
    float ye1 = e1.entityRect.y + e1.entityRect.h/2;
    float re1 = e1.entityRect.w/2;

    float xe2 = e2.entityRect.x + e2.entityRect.w/2;
    float ye2 = e2.entityRect.y + e2.entityRect.h/2;
    float re2 = e2.entityRect.w/2;
    
    //formula to check if two circles are touching
    return (((xe2 - xe1) * (xe2 - xe1) + (ye2 - ye1) * (ye2 - ye1)) <= ((re1 + re2) * (re1 + re2)) );
}

void Engine::handleBulletAstreoidCollision(std::list<Bullet>& bulletsUsed, std::list<Bullet>& bulletsNotUsed,
                                           std::list<Astreoid>& astreoidsUsed, std::list<Astreoid>& astreoidsNotUsed) {
    // Temporary lists to collect iterators to objects to be removed after collision checks
    std::list<std::list<Bullet>::iterator> bulletsToRemove;
    std::list<std::list<Astreoid>::iterator> astreoidsToRemove;

    for (auto aIt = astreoidsUsed.begin(); aIt != astreoidsUsed.end(); ++aIt) {

        for (auto bIt = bulletsUsed.begin(); bIt != bulletsUsed.end(); ++bIt) {
            if (checkCircCircCollision(*aIt, *bIt)) {
                bulletsToRemove.push_back(bIt);
                astreoidsToRemove.push_back(aIt);
                
                break; // Stop checking bullets for this asteroid, as it's already "destroyed"
            }
        }
    }

    // Move bullets and asteroids that collided to the unused lists using iterators
    for (auto bIt : bulletsToRemove) {
        bulletsNotUsed.splice(bulletsNotUsed.end(), bulletsUsed, bIt);
    }
    for (auto aIt : astreoidsToRemove) {
        astreoidsNotUsed.splice(astreoidsNotUsed.end(), astreoidsUsed, aIt);
    }
}
