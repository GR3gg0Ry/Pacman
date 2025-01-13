#pragma once

#define MAX_NAME 20
#include <unistd.h>
#include <sys/ioctl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

#include "Render.h"
#include "Input.h"

struct Configuration {
    std::size_t difficulty = 0;
    std::size_t map = 0;
};

class GameMenu {
public:
    GameMenu();

    std::vector<std::string> mainMenu();

    Configuration getConfig();
    
    

private:
    Input input_;
    char fileNames[MAX_NAME][MAX_NAME];
    std::vector<std::string> current_map_ = {
        "#############################",
        "#.....G.........#........O..#",
        "#O###.#####.###.#.###.###.#.#",
        "#.###.#.....#...#...#.....#.#",
        "#.###.#.###.###.###.#.###.#.#",
        "#.....#.#.....G.....#.#.....#",
        "#.###.#.#.#########.#.#.###.#",
        "#.###.#.#...........#.#.###.#",
        "#...G.#.#.###.###.###.#.....#",
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
        "#.....G.........#......O....#",
        "#############################"
    };
    Configuration configuration_;

    std::string maps_path_ = "./Maps";
    std::string config_path_ = "config.txt";
    std::vector<std::string> maps_paths_;

    int Map_counter();
    
    void chooseDifficulty();
    void chooseMap(int);

    std::vector<std::string> loadMap(const std::string& filePath);

    Configuration readConfig();
    void checkConfig(Configuration& config);
    void getFilesInDirectory();
};
