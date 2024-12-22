#pragma once

#include "Map.h"
#include "Entity.h"
#include "Input.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <filesystem>
#include <fstream>
#include <iostream>


class Game {
public:
    Game();
    int* menu(int);
    void pacmanMove();
    void ghostMove();
    void output();
    bool pacmanIsExist();
    void printGameOverScreen();
    int options();
    int bonuses();
    int map(int);
    int Map_counter();
    
private:
    Map map_;
    Pacman pacman_;
    std::vector<Ghost> ghosts_;
    Input input_;
    Point findOtherPortal(const Point& current_portal);
    bool isOccupiedByGhost(const Point& point);
    char fileNames[MAX_NAME][MAX_NAME];
};
