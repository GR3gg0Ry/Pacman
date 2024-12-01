#pragma once

#include <iostream>

struct Point {
    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    std::size_t x;
    std::size_t y;
};

struct Size {
    std::size_t width;
    std::size_t height;
};