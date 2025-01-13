#include <iostream>
#include <chrono>
#include <thread>

#include "GameMenu.h"
#include "Game.h"

using namespace std;

int main() {
    while (true) {
        GameMenu menu;
        Map map(menu.mainMenu());
        Configuration config = menu.getConfig();

        Game game(map, config);
        while (true) {
            
            game.printMap();
            
            if (game.pacmanIsExist()) {
                game.pacmanMove();
            } else {
                game.gameOver();
                sleep(3);
                break;
            }

            if (game.pacmanIsExist()) {
                game.ghostMove();
            } else {
                game.gameOver();
                sleep(3);
                break;
            }
        } 
    }
    return 0;
}
