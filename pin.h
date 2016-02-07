//
// Created by Ruslan on 07.02.2016.
//

#ifndef PROJECT_PIN_H
#define PROJECT_PIN_H

#include "point.h"

class Pin: public Point{
    unsigned int number;
public:
    Pin(Point point, unsigned int number);
};
#endif //PROJECT_PIN_H
