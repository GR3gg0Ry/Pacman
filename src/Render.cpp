#include "Render.h"

#include <iomanip>

namespace Render {
    void renderGameOver() {
        system("clear");
        std::cout << "\n";
        std::cout << "\033[1m\033[31m!Game Over!\033[0m\n";
        std::cout << "\033[1m\033[31mThanks for playing! Better luck next time.\033[0m\n";
    }

    void renderWin() {
        system("clear");
        std::cout << "\n";
        std::cout << "\033[1m\033[42mYou are winner! Thanks for playing! Press Esc to exit.\033[0m\n";
    }

    void renderScore(const int score) {
        system("clear");
        std::cout << "\033[1;32mScore: " << std::setw(5) << score << "\033[0m" << std::endl;
    }

    void renderMap(const std::vector<std::string>& map) {
        int flag=0;
        for (const auto& row : map) {
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
    if(flag==0)
        renderWin();
    }
}
