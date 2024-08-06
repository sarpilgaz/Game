#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>
#include "Player.h"
#include "Bullet.h"
#include "Astreoid.h"
#include "InputHandler.h"

class Engine {
    public:
        void updateGamestate(std::unordered_map<InputHandler::Keys, bool>& keystates, 
                            Player& player,
                            std::vector<Bullet>& bulletsUsed,
                            std::vector<Bullet>& bulletsNotUsed,
                            std::vector<Astreoid>& astreoidsUsed,
                            std::vector<Astreoid>& astreoidsNotUsed,
                            SDL_Renderer* renderer);

        void spawnAstreoid(std::vector<Astreoid>& astreoidsUsed, std::vector<Astreoid>& astreoidsUnUsed, SDL_Renderer* renderer);

        

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

        void handleShooting(std::unordered_map<InputHandler::Keys, bool>& keyStates, Player& player, std::vector<Bullet>& used, std::vector<Bullet>& notUsed);

        void updateBulletPositions(std::vector<Bullet>& used, std::vector<Bullet>& notUsed);

        void updateAstreoidPositions(std::vector<Astreoid>& used, std::vector<Astreoid>& notUsed);

        void spawnAstreoidRandomly(std::vector<Astreoid>& astreoidsUsed, std::vector<Astreoid>& astreoidsUnUsed, SDL_Renderer* renderer);
};

#endif