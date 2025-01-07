#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "GameState.h"

class StateManager {
private:
    GameState currentState;

public:
    StateManager() : currentState(GameState::Start) {}

    GameState getState() const {
        return currentState;
    }

    void changeState(GameState newState) {
        currentState = newState;
    }
};

#endif // STATE_MANAGER_H
