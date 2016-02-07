#include "point.h"

Point::Point(levelType level, cordType y, cordType x) {
    this->level = level;
    this->y = y;
    this->x = x;
}

Point::Point(const Point& point) {
    this->level = point.level;
    this->y = point.y;
    this->x = point.x;
}

bool operator== (Point &cP1, Point &cP2)
{
    return (cP1.x == cP2.x &&
            cP1.y == cP2.y &&
            cP1.level == cP2.level);
}

