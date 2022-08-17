#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "table.h"
#include <cmath>
#include <algorithm>

constexpr double over_two = 1.0 / 2.0;

static inline double point_distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
}

static inline double circle_distance(double x1, double y1, double x2, double y2, double radius)
{
    return std::max(point_distance(x1, y1, x2, y2) - radius, 0.0);
}

static inline double rectangle_distance(double x1, double y1, double x2, double y2, double width, double height)
{
    double dx = std::max(x1 - x2 - (width * over_two), 0.0);
    double dy = std::max(y1 - y2 - (height * over_two), 0.0);
    return sqrt(dx * dx + dy * dy) - 1.0;
}

#endif