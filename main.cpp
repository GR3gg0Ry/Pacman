#include <iostream>
#include <chrono>
#include <thread>

#include "Game.h"

using namespace std;

int main() {
    Game game;
    int* options = game.menu(game.Map_counter());
    
    while (true) {
        
        game.output();
        
        if (game.pacmanIsExist()) {
            game.pacmanMove();
        } else {
            game.printGameOverScreen();
            break;
        }

        if (game.pacmanIsExist()) {
            game.ghostMove();
        } else {
            game.printGameOverScreen();
            break;
        }
    }
    return 0;
}
