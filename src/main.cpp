#include <iostream>
#include "Game.h"

int main(int argc, char* args[]) {

    Game game;

    if (!game.init()) {
        std::cerr << "Error initializing game." << std::endl;
        return -1;
    }

    game.run();

    return 0;
}
