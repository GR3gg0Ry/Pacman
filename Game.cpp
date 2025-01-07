#include "Game.h"

Game::Game(Map map, Configuration config) : map_(map), 
               pacman_(&map_),
               input_(Input()),
               configuration_(config)
{
    std::vector<Point> ghost_coordinates = map_.getGhostStartCoordinates();
    for (std::size_t i = 0; i < ghost_coordinates.size(); ++i) {
        if (configuration_.difficulty == 0) {
            ghosts_.push_back(Ghost(ghost_coordinates[i], &map_, ghost_behaviors_[1]));
        } else if (configuration_.difficulty == 1) {
            ghosts_.push_back(Ghost(ghost_coordinates[i], &map_, ghost_behaviors_[i % ghost_behaviors_.size()]));
        } else {
            ghosts_.push_back(Ghost(ghost_coordinates[i], &map_, ghost_behaviors_[0]));
        }
    }
}

void Game::pacmanMove() {
    pacman_.move(input_.readchar());
}

void Game::ghostMove() {
    for (auto& ghost : ghosts_) {
        Point cur = ghost.getPoint();
        Point target = pacman_.getPoint();
        Point next = ghost.move(target);

        if (isOccupiedByGhost(next)) {
            continue;
        }

        if (map_.getField(next) == 'P') {
            pacman_.deadPacman();
        }

        map_.changeField(cur, ' ');
        map_.changeField(next, 'G');
        ghost.changePoint(next);
    }
}

bool Game::pacmanIsExist() {
    return pacman_.getExist();
}

void Game::gameOver() {
    std::cout << "\033[2J\033[H";
    Render::renderGameOver();
}

void Game::printMap() {
    map_.printMap();
}

bool Game::isOccupiedByGhost(Point p) {
    for (auto& ghost : ghosts_) {
        if (ghost.getPoint() == p) {
            return true;
        }
    }
    return false;
}
