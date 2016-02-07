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

