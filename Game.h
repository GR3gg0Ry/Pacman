#pragma once

#include "Map.h"
#include "Entity.h"
#include "Input.h"

class Game {
public:
    Game();
    void pacmanMove();
    void ghostMove();
    void output();
    bool pacmanIsExist();
    void printGameOverScreen();
private:
    Map map_;
    Pacman pacman_;
    std::vector<Ghost> ghosts_;
    Input input_;

    Point findOtherPortal(const Point& current_portal);
    bool isOccupiedByGhost(const Point& point);
};