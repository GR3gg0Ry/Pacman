#pragma once

#include <iomanip>

#include "Render.h"

class ScoreCounter {
public:
    void addScores(int scores) {
        score_ += scores;
    }

    int getScore() const {
        return score_;
    }

    void printScore() const {
        Render::renderScore(score_);
    }

private:
    int score_ = 0;
};
