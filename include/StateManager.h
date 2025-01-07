#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <unordered_map>
#include "GameState.h"
#include "InputHandler.h"
#include "Player.h"

class StateManager {
private:
    GameState currentState;

public:
    StateManager() : currentState(GameState::Menu) {}

    GameState getState() const {
        return currentState;
    }

    void changeState(GameState newState) {
        currentState = newState;
    }

    void handleState(Player& player, std::unordered_map<InputHandler::Keys, bool>& keystates) {
        switch (currentState) {
            case GameState::Menu:
                if (keystates[InputHandler::A]) {
                    currentState = GameState::Start;
                }
                
                break;

            case GameState::Start:
                if (player.getHealth() <= 0) {
                    currentState = GameState::End;
                }
                break;
            
            case GameState::End:
                if (keystates[InputHandler::A]) {
                    currentState = GameState::Restart;
                }
                break;
            case GameState::Restart:
                currentState = GameState::Menu;
        }
    }
};

#endif // STATE_MANAGER_H
