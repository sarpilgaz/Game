#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <list>
#include <list>
#include <cmath>
#include <ctime>
#include <iostream>
#include <array>
#include <limits>
#include "Player.h"
#include "Bullet.h"
#include "Astreoid.h"
#include "InputHandler.h"

class Engine {
    public:
        void updateGamestate(std::unordered_map<InputHandler::Keys, bool>& keystates, 
                            Player& player,
                            std::list<Bullet>& bulletsUsed,
                            std::list<Bullet>& bulletsNotUsed,
                            std::list<Astreoid>& astreoidsUsed,
                            std::list<Astreoid>& astreoidsNotUsed,
                            SDL_Renderer* renderer);

        void spawnAstreoid(std::list<Astreoid>& astreoidsUsed, std::list<Astreoid>& astreoidsUnUsed, SDL_Renderer* renderer);

        

    private:
        bool bulletShot = false;
        const float MAX_VELOCITY = 3.0f;
        const float VELOCITY_INCREMENT = 0.4f;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const int MIN_ASTREOID_VELOCITY = 2;
        const int MAX_ASTREOID_VELOCITY = 5;
        const int ASTREOID_SPAWN_OFFSET = 100;


        float randomFloat(float min, float max);

        void calculateRandomAstreoidVelocity(Astreoid& astreoid, float targetX, float targetY);

        void updatePlayerPosition(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player);

        int checkPlayerOutofBounds(const Player& player);

        void handleShooting(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player, std::list<Bullet>& used, std::list<Bullet>& notUsed);

        void updateBulletPositions(std::list<Bullet>& used, std::list<Bullet>& notUsed);

        void updateAstreoidPositions(std::list<Astreoid>& used, std::list<Astreoid>& notUsed);

        void spawnAstreoidRandomly(std::list<Astreoid>& astreoidsUsed, std::list<Astreoid>& astreoidsUnUsed, SDL_Renderer* renderer);

        bool checkCollisionsSAT(const Entity& e1, const Entity& e2);

        bool checkCircRectCollision(const Entity& circleEntity, const Entity& rectEntity);

        bool checkCircCircCollision(const Entity& e1, const Entity& e2);

        void projectOntoAxis(const std::array<SDL_Point, 4>& vertices, const SDL_Point& axis, float& min, float& max);

        void handleCollision(std::list<Astreoid>& astreoidsUsed, std::list<Bullet>& bulletsUsed, 
                                     std::list<Astreoid>& astreoidsNotUsed, std::list<Bullet>& bulletsNotUsed,
                                     std::list<Astreoid>::iterator& ait, std::list<Bullet>::iterator& bit, bool& erased);
};

#endif