#pragma once

#include "GameUtils.h"

class Entity {
public:
    Entity(Point p) : point_(p) {}
    
    void changePoint(Point p) {
        point_ = p;
    }

    Point getPoint() const {
        return point_;
    }
private:
    Point point_;
};


class Ghost : public Entity {
public:
    Ghost(Point p) : Entity(p) {}
};


class Pacman : public Entity {
public:
    Pacman(Point p) : Entity(p) {
        exist_ = true;
    }

    bool getExist() const {
        return exist_;
    }

    void deadPacman() {
        exist_ = false;
    }
private:
    bool exist_;
};
