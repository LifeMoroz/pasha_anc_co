#include "point.h"

Point::Point(cordType y, cordType x) {
    this->y = y;
    this->x = x;
}

Point::Point(const Point& point) {
    this->y = point.y;
    this->x = point.x;
}

bool operator== (Point &cP1, Point &cP2)
{
    return cP1.x == cP2.x && cP1.y == cP2.y;
}

bool operator!=(Point &cP1, Point &cP2) {
    return !(cP1 == cP2);
}
