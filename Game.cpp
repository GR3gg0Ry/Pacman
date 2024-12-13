#include "Game.h"

Game::Game() : map_(Map()), 
               pacman_(map_.getPacmanStartCoordinates()),
               input_(Input())
{
    std::vector<Point> ghost_coordinates = map_.getGhostStartCoordinates();
    for (const auto& coordinates : ghost_coordinates) {
        ghosts_.push_back(Ghost(coordinates));
    }
}

int* Game::menu() {
    struct winsize w;
    int menuSize=4;
    std::string menuItems[menuSize] = { "Start Game", "Options","Bonuses", "Exit" };
    int selectedItem = 0;
    int lev=2,bon=50;
    int* opt;
    
    while (true) {
        system("clear"); // Очистка 
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int strLength = 10;
        int padding = (w.ws_col - strLength) / 2;
        
        std::cout << "\033[42m" << std::string(w.ws_col, ' ') << "\033[0m" << '\n' << std::endl;
        for (int i = 0; i < menuSize; i++) {
            if (i == selectedItem) {
                std::cout << std::string(padding, ' ') << "> " << menuItems[i] << " <" << std::endl; // Выделенный элемент
            } else {
                std::cout << std::string(padding, ' ') << "  " << menuItems[i] << std::endl;
            }
        }

        char key = input_.readmenu(); // Считывание нажатой клавиши

        if (key == 'w') { // Стрелка вверх
            selectedItem = (selectedItem - 1 + menuSize) % menuSize;
        } else if (key == 's') { // Стрелка вниз
            selectedItem = (selectedItem + 1) % menuSize;
        } else if (key == '\n') {
            if (selectedItem == 3) {
            system("clear");
                std::cout << "Exiting..." << std::endl;
                exit(0); // Выход из программы
            }
            else if (selectedItem == 0) {
            system("clear");
                break;
            }
            else if (selectedItem == 1) {
                lev = options();
            }
            else if (selectedItem == 2) {
                bon = bonuses();
            }
        }
        
    }
    opt[1]=lev;
    opt[2]=bon;
    return opt;
}

int Game::options() {
    struct winsize w;
    int menuSize=3;
    std::string menuItems[menuSize] = { "Easy", "Normal", "Hard" };
    int selectedItem = 0;
    int lev;
    
    while (true) {
        system("clear"); // Очистка 
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int strLength = 4;
        int padding = (w.ws_col - strLength) / 2;
        
        std::cout << "\033[41m" << std::string(w.ws_col, ' ') << "\033[0m" << '\n' << std::endl;
        for (int i = 0; i < menuSize; i++) {
            if (i == selectedItem) {
                std::cout << std::string(padding, ' ') << "> " << menuItems[i] << " <" << std::endl; // Выделенный элемент
            } else {
                std::cout << std::string(padding, ' ') << "  " << menuItems[i] << std::endl;
            }
        }

        char key = input_.readmenu(); // Считывание нажатой клавиши
        
        if (key == 'w') { // Стрелка вверх
            selectedItem = (selectedItem - 1 + menuSize) % menuSize;
        } else if (key == 's') { // Стрелка вниз
            selectedItem = (selectedItem + 1) % menuSize;
        } else if (key == '\n') {
            if (selectedItem == 2) {
              lev = 3;
              break;
            }
            else if (selectedItem == 0) {
                lev = 1;
                break;
            }
            else if (selectedItem == 1) {
                lev = 2;
                break;
            }
        }
        
    }

    return lev;
}

int Game::bonuses() {
    struct winsize w;
    int menuSize=7;
    std::string menuItems[menuSize] = { "20", "25","30","35","40","45","50" };
    int selectedItem = 0;
    int bon=40;
    
    while (true) {
        system("clear"); // Очистка 
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int strLength = 2;
        int padding = (w.ws_col - strLength) / 2;
        
        std::cout << "\033[41m" << std::string(w.ws_col, ' ') << "\033[0m" << '\n' << std::endl;
        for (int i = 0; i < menuSize; i++) {
            if (i == selectedItem) {
                std::cout << std::string(padding, ' ') << "> " << menuItems[i] << " <" << std::endl; // Выделенный элемент
            } else {
                std::cout << std::string(padding, ' ') << "  " << menuItems[i] << std::endl;
            }
        }

        char key = input_.readmenu(); // Считывание нажатой клавиши
        
        if (key == 'w') { // Стрелка вверх
            selectedItem = (selectedItem - 1 + menuSize) % menuSize;
        } else if (key == 's') { // Стрелка вниз
            selectedItem = (selectedItem + 1) % menuSize;
        } else if (key == '\n') {
          switch(selectedItem) {
          case 0: bon=20;
          break;
          case 1: bon=25;
          break;
          case 2: bon=30;
          break;
          case 3: bon=35;
          break;
          case 4: bon=40;
          break;
          case 5: bon=45;
          break;
          case 6: bon=50;
          break;
          }
          break;
    }
    }

    return bon;
}

void Game::pacmanMove() {
    Point current_point = pacman_.getPoint();
    Point next_point = current_point;

    char move = input_.readchar();
        switch (move) {
        case 'w': case 'W': 
            next_point.y -= 1;
            break;
        case 's': case 'S': 
            next_point.y += 1;
            break;
        case 'a': case 'A': 
            next_point.x -= 1;
            break;
        case 'd': case 'D': 
            next_point.x += 1;
            break;
        default:
            return;
    }

    char next_field = map_.getField(next_point.x, next_point.y);
    if (next_field == '#') {
        return;
    }

    switch (next_field) {
        case '.':
            map_.addScores(10);
            break;
        case 'O':
            map_.addScores(50);
            break;
        case 'T': {
            Point teleport_point = findOtherPortal(next_point);
            next_point = teleport_point;
            break;
        }
        case 'G': {
            pacman_.deadPacman();
            break;
        }
        default:
            break;
    }

    if (!pacman_.getExist()) {
        return;
    }

    map_.changeField(current_point.x, current_point.y, ' ');
    map_.changeField(next_point.x, next_point.y, 'P');
    pacman_.changePoint(next_point);
}

void Game::ghostMove() {
    int i = 0;
    for (auto& ghost : ghosts_) {
        Point current_point = ghost.getPoint();
        Point target_point = pacman_.getPoint();
        Point next_point = current_point;

        if (i % 2 == 0) {
            // Логика движения обычного призрака: следовать за Pac-Man
            if (target_point.x > current_point.x && map_.getField(current_point.x + 1, current_point.y) != '#') {
                next_point.x += 1;
            } else if (target_point.x < current_point.x && map_.getField(current_point.x - 1, current_point.y) != '#') {
                next_point.x -= 1;
            } else if (target_point.y > current_point.y && map_.getField(current_point.x, current_point.y + 1) != '#') {
                next_point.y += 1;
            } else if (target_point.y < current_point.y && map_.getField(current_point.x, current_point.y - 1) != '#') {
                next_point.y -= 1;
            }
        } else if (i % 2 != 0) {
            // Логика для другого типа призрака (например, случайное движение)
            int randomDirection = rand() % 4;
            switch (randomDirection) {
            case 0:
                if (map_.getField(current_point.x + 1, current_point.y) != '#')
                    next_point.x += 1;
                break;
            case 1:
                if (map_.getField(current_point.x - 1, current_point.y) != '#')
                    next_point.x -= 1;
                break;
            case 2:
                if (map_.getField(current_point.x, current_point.y + 1) != '#')
                    next_point.y += 1;
                break;
            case 3:
                if (map_.getField(current_point.x, current_point.y - 1) != '#')
                    next_point.y -= 1;
                break;
            }
        }

        // Проверка на столкновение с другими призраками
        if (isOccupiedByGhost(next_point)) {
            continue;  // Если клетка занята другим призраком, не двигаемся
        }

        // Проверяем, есть ли Pac-Man на следующей клетке
        if (map_.getField(next_point.x, next_point.y) == 'P') {
            pacman_.deadPacman();
        }

        // Обновляем позицию демона на карте
        map_.changeField(current_point.x, current_point.y, ' ');
        map_.changeField(next_point.x, next_point.y, 'G');
        ghost.changePoint(next_point);

        ++i;
    }
}

void Game::output() {
    map_.renderMap();
}

bool Game::pacmanIsExist() {
    return pacman_.getExist();
}

void Game::printGameOverScreen() {
    std::vector<std::string> game_over_art = {
        "  #####     #    #     #  #######     ###### #         #  #######  #####  ",
        " #     #   # #   ##   ##  #           #    #  #       #   #        #    # ",
        " #        #####  # ### #  #######     #    #   #     #    #######  #####  ",
        " #  #### #     # #     #  #           #    #    #   #     #        #   #  ",
        " #     # #     # #     #  #           #    #     # #      #        #    # ",
        "  #####  #     # #     #  #######     ######      #       #######  #     #"
    };

    // Очищаем экран
    system("clear");

    // Печатаем надпись "GAME OVER" в стиле карты
    for (const auto& row : game_over_art) {
        for (const auto& cell : row) {
            switch (cell) {
                case '#':
                    std::cout << "\033[41m  \033[0m"; // Красный фон
                    break;
                case ' ':
                    std::cout << "  "; // Пробел
                    break;
                default:
                    std::cout << cell << " ";
                    break;
            }
        }
        std::cout << std::endl;
    }

    // Вывод сообщения ниже надписи
    std::cout << "\n";
    std::cout << "\033[1m\033[31mThanks for playing! Better luck next time.\033[0m\n";
    std::cout << "\033[1m\033[32mPress 'R' to Restart\nPress 'Q' to Quit\n\033[0m";
}

Point Game::findOtherPortal(const Point& current_portal) {
    Point teleport_point;

    for (std::size_t y = 0; y < map_.getMapSize().height; ++y) {
        for (std::size_t x = 0; x < map_.getMapSize().width; ++x) {
            if (map_.getField(x, y) == 'T' && !(x == current_portal.x && y == current_portal.y)) {
                teleport_point = {x, y};
            }
        }
    }

    if (teleport_point.x == 0) {
        teleport_point.x += 1;
    } else if (teleport_point.y == 0) {
        teleport_point.y += 1;
    } else if (teleport_point.x == map_.getMapSize().width - 1) {
        teleport_point.x -= 1;
    } else if (teleport_point.y == map_.getMapSize().height - 1) {
        teleport_point.y -= 1;
    }

    return teleport_point;
}

bool Game::isOccupiedByGhost(const Point& point) {
    for (const auto& ghost : ghosts_) {
        if (ghost.getPoint() == point) {
            return true;
        }
    }
    return false;
}
