//
// Created by ivan on 08.02.16.
//

#include "PolygonPoint.h"

PolygonPoint::PolygonPoint(cordType y, cordType x) {
    this->y = y;
    this->x = x;
}

PolygonPoint::PolygonPoint(const PolygonPoint& point) {
    this->y = point.y;
    this->x = point.x;
}
