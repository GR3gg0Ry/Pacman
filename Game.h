#pragma once

#include "Map.h"
#include "Entity.h"
#include "Input.h"
#include "Render.h"
#include "GameMenu.h"

class Game {
public:
    Game(Map map, Configuration config);

    void pacmanMove();
    void ghostMove();

    bool pacmanIsExist();

    void gameOver();
    void printMap();

private:
    Map map_;
    Pacman pacman_;
    std::vector<Ghost> ghosts_;
    Input input_;
    Configuration configuration_;

    std::vector<GhostBehavior> ghost_behaviors_ = {
        FOLLOW_PACMAN,
        RANDOM
    };

    bool isOccupiedByGhost(Point p);
};
