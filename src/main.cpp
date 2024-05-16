#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace std;

int main(int argc, char* args[]) {
    cout << "Success!" << endl;
    
    Game game;
    
    if (!game.init()) {
        cerr << "Error initializing SDL." << endl;
        return -1;
    }

    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();

    cout << "Success!" << endl;

    return 0;
}