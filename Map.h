#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "GameUtils.h"
#include "ScoreCounter.h"

class Map {
public:
    Map();
    char getField(std::size_t x, std::size_t y);
    Size getMapSize();
    void changeField(std::size_t x, std::size_t y, char symbol);
    Point getPacmanStartCoordinates();
    std::vector<Point> getGhostStartCoordinates();
    void addScores(int scores);
    void renderMap();
    void Map_change(int);
    void inputpath(std::string);
private:
    std::vector<std::string> map_ = {
        "#############################",
        "#...............#........O..#",
        "#O###.#####.###.#.###.###.#.#",
        "#.###.#.....#...#...#.....#.#",
        "#.###.#.###.###.###.#.###.#.#",
        "#.....#.#.....G.....#.#.....#",
        "#.###.#.#.#########.#.#.###.#",
        "#.###.#.#...........#.#.###.#",
        "#.....#.#.###.###.###.#.....#",
        "#####.#.#.#.......#.#.#.#####",
        "#.......#.#.......#.#.......#",
        "#.#######.#...P...#.#######.#",
        "T...........................T",
        "#####.#.#.#.......#.#.#.#####",
        "#.....#.#.#.###.###.#.#...G.#",
        "#.###.#.#...........#.#.###.#",
        "#.###.#.#.#########.#.#.###.#",
        "#.O...#G#...........#.#.....#",
        "#.###.#.###.###.###.#.###.#.#",
        "#.###.#.....#...#...#.....#.#",
        "#.###.#####.###.#.###.###.#.#",
        "#...............#......O....#",
        "#############################"
    };
    
    Size map_size_;
    Point pacman_start_coordinates_;
    std::vector<Point> ghost_start_coordinates_;
    ScoreCounter score_counter_;
    std::string pathm;
    bool checkField(std::size_t x, std::size_t y);
    Point findPacmanStartCoordinates();
    std::vector<Point> findGhostStartCoordinates();
};
