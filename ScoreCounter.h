#pragma once

#include <iostream>
#include <iomanip>

class ScoreCounter {
public:
    void addScores(int scores) {
        score_ += scores;
    }

    int getScore() const {
        return score_;
    }

    void renderScore() const {
        std::cout << "\033[1;32mScore: " << std::setw(5) << score_ << "\033[0m" << std::endl;
    }

private:
    int score_ = 0;
};
