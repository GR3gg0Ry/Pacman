#include "Entity.h"

Entity::Entity(Point p, Map* map) : point_(p), map_(map) {}

void Entity::changePoint(Point p) {
    point_ = p;
}

Point Entity::getPoint() const {
    return point_;
}

Map* Entity::getMap() const {
    return map_;
}


Ghost::Ghost(Point p, Map* map, GhostBehavior behavior) : Entity(p, map), behavior_(behavior) {}

Point Ghost::move(Point pacman_position) {
    Point next_position = this->getPoint();

    switch (behavior_) {
        case FOLLOW_PACMAN:
            next_position = moveTowardsPacman(pacman_position);
            break;
        case RANDOM:
            next_position = randomMove();
            break;
    }

    return next_position;
}

Point Ghost::moveTowardsPacman(Point pacman) {
    Point cur = this->getPoint();
    Point next = cur;
    if (pacman.x > cur.x && checkMapField({cur.x + 1, cur.y})) {
        next.x += 1;
    } else if (pacman.x < cur.x && checkMapField({cur.x - 1, cur.y})) {
        next.x -= 1;
    } else if (pacman.y > cur.y && checkMapField({cur.x, cur.y + 1})) {
        next.y += 1;
    } else if (pacman.y < cur.y && checkMapField({cur.x, cur.y - 1})) {
        next.y -= 1;
    }
    return next;
}

Point Ghost::randomMove() {
    Point cur = this->getPoint();
    Point next = cur;
    int randomDirection = rand() % 4;

    switch (randomDirection) {
        case 0:
            if (checkMapField({cur.x + 1, cur.y})) next.x += 1;
            break;
        case 1:
            if (checkMapField({cur.x - 1, cur.y})) next.x -= 1;
            break;
        case 2:
            if (checkMapField({cur.x, cur.y + 1})) next.y += 1;
            break;
        case 3:
            if (checkMapField({cur.x, cur.y - 1})) next.y -= 1;
            break;
    }
    return next;
}

bool Ghost::checkMapField(Point p) const {
    auto field = getMap()->getField(p);
    if (field != '#' && field != 'T') {
        return true;
    }
    return false;
}


Pacman::Pacman(Map* map) : Entity(map->getPacmanStartCoordinates(), map) {
    exist_ = true;
}

bool Pacman::getExist() const {
    return exist_;
}

void Pacman::deadPacman() {
    exist_ = false;
}

void Pacman::move(char symbol) {
    Point cur = getPoint();
    Point next = cur;

    switch (symbol) {
        case 'w': case 'W': 
            next.y -= 1;
            break;
        case 's': case 'S': 
            next.y += 1;
            break;
        case 'a': case 'A': 
            next.x -= 1;
            break;
        case 'd': case 'D': 
            next.x += 1;
            break;
        default:
            return;
    }

    char next_field = getMap()->getField(next);
    if (next_field == '#') {
        return;
    }

    switch (next_field) {
        case '.':
            getMap()->addScores(10);
            break;
        case 'O':
            getMap()->addScores(50);
            break;
        case 'T': {
            Point teleport = getMap()->findOtherPortal(next);
            next = teleport;
            break;
        }
        case 'G': {
            this->deadPacman();
            break;
        }
        default:
            break;
    }

    if (!this->getExist()) {
        return;
    }

    getMap()->changeField(cur, ' ');
    getMap()->changeField(next, 'P');
    this->changePoint(next);
}