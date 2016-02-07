//
// Created by Ruslan on 07.02.2016.
//

#ifndef PROJECT_PIN_H
#define PROJECT_PIN_H

#include "point.h"

class Pin: public Point{
public:
    Pin(Point point, int number);
    pointType number;
};
#endif //PROJECT_PIN_H
