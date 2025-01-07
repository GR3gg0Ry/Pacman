#include "GameMenu.h"

namespace fs = std::filesystem;

GameMenu::GameMenu() : input_(Input()) {
    getFilesInDirectory();
    configuration_ = readConfig();
}

std::vector<std::string> GameMenu::mainMenu() {
    int maps = this->Map_counter();
    struct winsize w;
    const int menu_size = 4;
    std::string menuItems[menu_size] = {"Start Game", "Choose Difficulty", "Choose Map", "Exit"};
    int selectedItem = 0;
    
    while (true) {
        system("clear"); 
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int strLength = 10;
        int padding = (w.ws_col - strLength) / 2;

        std::cout << "\033[42m" << std::string(w.ws_col, ' ') << "\033[0m" << '\n' << std::endl;
        for (int i = 0; i < menu_size; i++) {
            if (i == selectedItem) {
                std::cout << std::string(padding, ' ') << "> " << menuItems[i] << " <" << std::endl;
            } else {
                std::cout << std::string(padding, ' ') << "  " << menuItems[i] << std::endl;
            }
        }

        char key = input_.readmenu();

        if (key == 'w') {
            selectedItem = (selectedItem - 1 + menu_size) % menu_size;
        } else if (key == 's') {
            selectedItem = (selectedItem + 1) % menu_size;
        } else if (key == '\n') {
            if (selectedItem == 3) {
                system("clear");
                std::cout << "Exiting..." << std::endl;
                exit(0);
            } else if (selectedItem == 0) {
                system("clear");
                break;
            } else if (selectedItem == 1) {
                chooseDifficulty();
            } else if (selectedItem == 2) {
                chooseMap(maps);
            }
        } 
    }

    current_map_ = loadMap(maps_paths_[configuration_.map]);
    return current_map_;
}

Configuration GameMenu::getConfig() {
    return configuration_;
}

void GameMenu::chooseDifficulty() {
    struct winsize w;
    const int menu_size = 3;
    std::string menuItems[menu_size] = {"Easy", "Normal", "Hard"};
    int selectedItem = 0;
    
    while (true) {
        system("clear");
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int strLength = 4;
        int padding = (w.ws_col - strLength) / 2;
        
        std::cout << "\033[41m" << std::string(w.ws_col, ' ') << "\033[0m" << '\n' << std::endl;
        for (int i = 0; i < menu_size; i++) {
            if (i == selectedItem) {
                std::cout << std::string(padding, ' ') << "> " << menuItems[i] << " <" << std::endl;
            } else {
                std::cout << std::string(padding, ' ') << "  " << menuItems[i] << std::endl;
            }
        }

        char key = input_.readmenu();
        
        if (key == 'w') {
            selectedItem = (selectedItem - 1 + menu_size) % menu_size;
        } else if (key == 's') {
            selectedItem = (selectedItem + 1) % menu_size;
        } else if (key == '\n') {
            if (selectedItem == 2) {
              configuration_.difficulty = 2;
              break;
            } else if (selectedItem == 0) {
                configuration_.difficulty = 0;
                break;
            } else if (selectedItem == 1) {
                configuration_.difficulty = 1;
                break;
            }
        }
    }
}

void GameMenu::chooseMap(int maps) {
if(maps==0) {

      return ;}
    struct winsize w;
    const int menuSize=maps+1;
    int selectedItem = 0;

    int map=0;
    
    while (true) {
        system("clear"); // Очистка 


        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int strLength = 2;
        int padding = (w.ws_col - strLength) / 2;

        
        std::cout << "\033[41m" << std::string(w.ws_col, ' ') << "\033[0m" << '\n' << std::endl;

        for (int i = 0; i < menuSize; i++) {

            if (i == selectedItem) {
                std::cout << std::string(padding, ' ') << "> " << fileNames[i] << " <" << std::endl; // Выделенный элемент
            } else {
                std::cout << std::string(padding, ' ') << "  " << fileNames[i] << std::endl;

            }
        }

        char key = input_.readmenu(); // Считывание нажатой клавиши
        
        if (key == 'w') { // Стрелка вверх

            selectedItem = (selectedItem - 1 + menuSize) % menuSize;
        } else if (key == 's') { // Стрелка вниз

            selectedItem = (selectedItem + 1) % menuSize;

        } else if (key == '\n') {

          configuration_.map = selectedItem-1;
          break;
    }
}
    
}

int GameMenu::Map_counter()
{    
    std::string path = "./Maps";
    strncpy(fileNames[0],"DEFAULT",MAX_NAME);

    int fileCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {

        if (entry.is_regular_file()) {
            fileCount++;
            strncpy(fileNames[fileCount],entry.path().filename().string().c_str(),MAX_NAME);
            fileNames[fileCount][MAX_NAME] = '\0';
        }
    } 
    return fileCount;
}

std::vector<std::string> GameMenu::loadMap(const std::string& filePath) {
    if (this->configuration_.map == -1)
        return current_map_;
    std::vector<std::string> map;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filePath << std::endl;
        return map;
    }

    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
    }

    file.close();
    return map;
}

Configuration GameMenu::readConfig() {
    Configuration config;
    std::ifstream config_file(config_path_);

    if (!config_file) {
        std::cerr << "Error: Cannot open file " << config_path_ << std::endl;
        return configuration_;
    }

    std::string line;
    while (std::getline(config_file, line)) {
        if (line.empty()) continue;

        auto delimiter_pos = line.find('=');
        if (delimiter_pos == std::string::npos) {
            std::cerr << "Warning: Malformed line in config file: " << line << std::endl;
            continue;
        }

        std::string key = line.substr(0, delimiter_pos);
        std::string value = line.substr(delimiter_pos + 1);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);

        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        if (!value.empty() && value.front() == '"' && value.back() == '"') {
            value = value.substr(1, value.size() - 2);
        }

        if (key == "difficulty") {
            config.difficulty = std::stoi(value);
        } else if (key == "map") {
            config.map = std::stoi(value);
        }
    }

    checkConfig(config);

    config_file.close();

    return config;
}

void GameMenu::checkConfig(Configuration& config) {
    if (config.difficulty > 2) {
        config.difficulty = 0;
    }
    if (config.map >= maps_paths_.size()) {
        config.map = 0;
    }
}

void GameMenu::getFilesInDirectory() {
    std::vector<std::string> file_paths;

    try {
        for (const auto& entry : fs::directory_iterator(maps_path_)) {
            if (entry.is_regular_file()) {
                file_paths.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: Cannot open directory " << e.what() << std::endl;
    }

    maps_paths_ = file_paths;
}
