//
// Created by Ruslan on 07.02.2016.
//

#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H
#include <string>
#include "point.h"
#include "pin.h"

Pin line_to_pin(std::string s1, char delim);
std::vector<Pin> read_pin_coordinates(std::string);
#endif //PROJECT_UTILS_H
