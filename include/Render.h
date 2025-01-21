#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace Render {
    void renderGameOver();
    void renderWin();
    void renderScore(const int score);
    void renderMap(const std::vector<std::string>& map);
}
