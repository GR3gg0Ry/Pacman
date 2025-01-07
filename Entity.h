#pragma once

#include "GameUtils.h"
#include "Map.h"

enum GhostBehavior {
    FOLLOW_PACMAN,
    RANDOM
};


class Entity {
public:
    Entity(Point p, Map* map);

    void changePoint(Point p);
    Point getPoint() const;
    
    Map* getMap() const;

private:
    Point point_;
    Map* map_;
};


class Ghost : public Entity {
public:
    Ghost(Point p, Map* map, GhostBehavior behavior);

    Point move(Point pacman_position);

private:
    GhostBehavior behavior_;

    Point moveTowardsPacman(Point pacman_position);
    Point randomMove();

    bool checkMapField(Point p) const; 
};


class Pacman : public Entity {
public:
    Pacman(Map* map);

    bool getExist() const;
    void deadPacman();

    void move(char symbol);

private:
    bool exist_;
};
