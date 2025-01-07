#pragma once

#include <string>
#include <vector>

#include "GameUtils.h"
#include "ScoreCounter.h"
#include "Render.h"

class Map {
public:
    Map(const std::vector<std::string>& map);

    char getField(Point p) const;
    void changeField(Point p, char symbol);

    Size getMapSize();

    Point getPacmanStartCoordinates() const;
    std::vector<Point> getGhostStartCoordinates() const;

    Point findOtherPortal(Point cur_portal);

    void addScores(int scores);

    void printMap();
    
private:
    std::vector<std::string> map_;
    ScoreCounter score_counter_;
    Size map_size_;
    Point pacman_start_coordinates_;
    std::vector<Point> ghost_start_coordinates_;

    bool checkField(Point p) const;
    
    Point findPacmanStartCoordinates();
    std::vector<Point> findGhostStartCoordinates();
};
