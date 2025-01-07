#include "Map.h"

#include <iostream>

Map::Map(const std::vector<std::string>& map) : map_(map) {
    map_size_ = {map_[0].size(), map_.size()};
    pacman_start_coordinates_ = findPacmanStartCoordinates();
    ghost_start_coordinates_ = findGhostStartCoordinates();
}

char Map::getField(Point p) const {
    if (checkField(p)) {
        return map_[p.y][p.x];
    }
    return ' ';
}

void Map::changeField(Point p, char symbol) {
    if (checkField(p)) {
        map_[p.y][p.x] = symbol;
    }
}

Size Map::getMapSize() {
    return map_size_;
}

Point Map::getPacmanStartCoordinates() const {
    return pacman_start_coordinates_;
}

std::vector<Point> Map::getGhostStartCoordinates() const {
    return ghost_start_coordinates_;
}

Point Map::findOtherPortal(Point cur_portal) {
    Point teleport;

    for (std::size_t y = 0; y < map_size_.height; ++y) {
        for (std::size_t x = 0; x < map_size_.width; ++x) {
            if (map_[y][x] == 'T' && !(x == cur_portal.x && y == cur_portal.y)) {
                teleport = {x, y};
            }
        }
    }

    if (teleport.x == 0) {
        teleport.x += 1;
    } else if (teleport.y == 0) {
        teleport.y += 1;
    } else if (teleport.x == map_size_.width - 1) {
        teleport.x -= 1;
    } else if (teleport.y == map_size_.height - 1) {
        teleport.y -= 1;
    }

    return teleport;
}

void Map::addScores(int scores) {
    score_counter_.addScores(scores);
}

void Map::printMap() {
    std::cout << "\033[2J\033[H";
    score_counter_.printScore();
    std::cout << std::endl;
    Render::renderMap(map_);
}

bool Map::checkField(Point p) const {
    if (p.y <= map_size_.height && p.x <= map_size_.width) {
        return true;
    }
    return false;
}

Point Map::findPacmanStartCoordinates() {
    Point pacman;
    for (std::size_t y = 0; y < map_size_.height; ++y) {
        for (std::size_t x = 0; x < map_size_.width; ++x) {
            if (map_[y][x] == 'P') {
                pacman = {x, y};
            }
        }
    }
    return pacman;
}

std::vector<Point> Map::findGhostStartCoordinates() {
    std::vector<Point> ghosts;
    for (std::size_t y = 0; y < map_size_.height; ++y) {
        for (std::size_t x = 0; x < map_size_.width; ++x) {
            if (map_[y][x] == 'G') {
                ghosts.push_back({x, y});
            }
        }
    }
    return ghosts;
}
