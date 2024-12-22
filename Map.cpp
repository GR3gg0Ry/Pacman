#include "Map.h"

#include <iostream>

Map::Map() {
    map_size_ = {map_[0].size(), map_.size()};
    pacman_start_coordinates_ = findPacmanStartCoordinates();
    ghost_start_coordinates_ = findGhostStartCoordinates();
}

char Map::getField(std::size_t x, std::size_t y) {
    if (checkField(x, y)) {
        return map_[y][x];
    }
    return ' ';
}

Size Map::getMapSize() {
    return map_size_;
}

void Map::changeField(std::size_t x, std::size_t y, char symbol) {
    if (checkField(x, y)) {
        map_[y][x] = symbol;
    }
}

Point Map::getPacmanStartCoordinates() {
    return pacman_start_coordinates_;
}

std::vector<Point> Map::getGhostStartCoordinates() {
    return ghost_start_coordinates_;
}

void Map::addScores(int scores) {
    score_counter_.addScores(scores);
}

void Map::Map_change(char* names) {
    if (strcmp(names,"DEFAULT")){
    std::string name(names);
    
    std::string filePath = "./Map/" + name; 
    
    std::ifstream file(filePath);
    std::vector<std::string> lines;
    
    if (!file.is_open()) 
        std::cerr << "Ошибка при открытии файла: " << filePath << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    map_ = lines; }
    else {
          map_ = {
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
    }
    
} 

void Map::renderMap() {
    std::cout << "\033[2J\033[H"; // Очистка экрана и установка курсора в начало
    score_counter_.renderScore();
    std::cout << std::endl;
    for (const auto& row : map_) {
        for (const auto& cell : row) {
            switch (cell) {
                case '#':
                    std::cout << "\033[44m  \033[0m"; // Синий фон
                    break;
                case '.':
                    std::cout << "\033[93m.\033[0m "; // Желтая точка
                    break;
                case 'P':
                    std::cout << "\033[33mP\033[0m "; // Желтый Pac-Man
                    break;
                case 'G':
                    std::cout << "\033[91mG\033[0m "; // Красный призрак
                    break;
                case 'O':
                    std::cout << "\033[95mO\033[0m "; // Фиолетовый бонус
                    break;
                case 'T':
                    std::cout << "\033[94mT\033[0m "; // Голубой портал
                    break;
                case ' ':
                    std::cout << "  ";
                    break;
                default:
                    std::cout << cell << " ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

bool Map::checkField(std::size_t x, std::size_t y) {
    if (y <= map_size_.height && x <= map_size_.width) {
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
