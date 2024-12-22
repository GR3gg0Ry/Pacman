#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

#include "Game.h"

using namespace std;

int main() {
    
    while(true) {
    Game game;
    int* options = game.menu(game.Map_counter());
    
    while (true) {
        
        game.output();
        
        if (game.pacmanIsExist()) {
            game.pacmanMove();
        } else {
            game.printGameOverScreen();
            sleep(3);
            break;
        }

        if (game.pacmanIsExist()) {
            game.ghostMove();
        } else {
            game.printGameOverScreen();
            sleep(3);
            break;
        }
    } }
    return 0;
}
