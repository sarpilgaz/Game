#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <list>
#include <cmath>
#include <ctime>
#include <iostream>
#include <array>
#include <limits>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Astreoid.h"
#include "InputHandler.h"
#include "StateManager.h"

class Engine {
    public:
        Engine(StateManager& sm) : stateManager(sm) {}
        void updateGamestate(std::unordered_map<InputHandler::Keys, bool>& keystates, 
                            Player& player,
                            std::list<Bullet>& bulletsUsed,
                            std::list<Bullet>& bulletsNotUsed,
                            std::list<Astreoid>& astreoidsUsed,
                            std::list<Astreoid>& astreoidsNotUsed,
                            bool spawnAstreoid,
                            SDL_Renderer* renderer);

        

    private:
        StateManager& stateManager;
        bool bulletShot = false;
        const float MAX_VELOCITY = 3.0f;
        const float VELOCITY_INCREMENT = 0.4f;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const int MIN_ASTREOID_VELOCITY = 2;
        const int MAX_ASTREOID_VELOCITY = 5;
        const int ASTREOID_SPAWN_OFFSET = 100;


        void updateGameScene(std::unordered_map<InputHandler::Keys, bool>& keystates, 
                            Player& player,
                            std::list<Bullet>& bulletsUsed,
                            std::list<Bullet>& bulletsNotUsed,
                            std::list<Astreoid>& astreoidsUsed,
                            std::list<Astreoid>& astreoidsNotUsed,
                            bool spawnAstreoid,
                            SDL_Renderer* renderer);

        void restartGameState(Player& player,
                            std::list<Bullet>& bulletsUsed,
                            std::list<Bullet>& bulletsNotUsed,
                            std::list<Astreoid>& astreoidsUsed,
                            std::list<Astreoid>& astreoidsNotUsed,
                            bool spawnAstreoid);

        float randomFloat(float min, float max);

        void calculateRandomAstreoidVelocity(float& velX, float& velY, float x, float y, float targetX, float targetY);

        void updatePlayerPosition(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player);

        int checkPlayerOutofBounds(const Player& player);

        void handleShooting(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player, std::list<Bullet>& used, std::list<Bullet>& notUsed);

        void updateBulletPositions(std::list<Bullet>& used, std::list<Bullet>& notUsed);

        void updateAstreoidPositions(std::list<Astreoid>& used, std::list<Astreoid>& notUsed);

        void spawnAstreoidRandomly(std::list<Astreoid>& astreoidsUsed, std::list<Astreoid>& astreoidsUnUsed, SDL_Renderer* renderer);

        bool checkCollisionsSAT(const Entity& e1, const Entity& e2);

        bool checkCircRectCollision(const Entity& circleEntity, const Entity& rectEntity);

        bool checkCircCircCollision(const Entity& e1, const Entity& e2);

        bool checkCircTriangleCollision(const Entity& circleEntity, const Entity& triangleEntity);

        void projectOntoAxis(const std::vector<SDL_Point>& vertices, const SDL_Point& axis, float& min, float& max);

        void handleBulletAstreoidCollision(Player& player, std::list<Bullet>& bulletsUsed, std::list<Bullet>& bulletsNotUsed,
                                           std::list<Astreoid>& astreoidsUsed, std::list<Astreoid>& astreoidsNotUsed);

        void handleAstreoidPlayerCollision(Player& player, std::list<Astreoid>& astreoidsUsed, std::list<Astreoid>& astreoidsNotUsed);
};

#endif