#pragma once

#include "Map.h"
#include "Entity.h"
#include "Input.h"
#include <unistd.h>
#include <sys/ioctl.h>

class Game {
public:
    Game();
    int* menu();
    void pacmanMove();
    void ghostMove();
    void output();
    bool pacmanIsExist();
    void printGameOverScreen();
    int options();
    int bonuses();
private:
    Map map_;
    Pacman pacman_;
    std::vector<Ghost> ghosts_;
    Input input_;

    Point findOtherPortal(const Point& current_portal);
    bool isOccupiedByGhost(const Point& point);
};
