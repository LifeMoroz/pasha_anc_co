//
// Created by Ruslan on 07.02.2016.
//
#include <stdlib.h>
#include <fstream>
#include <assert.h>
#include <vector>
#include <iostream>
#include "utils.h"
#include <algorithm>

void pop_front_number(std::string s, char delim, int pos, int &new_pos, float &value) {
    int i = s.find_first_of(delim, pos);
    if (i!=-1) {
        value = atof(s.substr(pos, i).c_str());
    }
    else
        value = atof(s.substr(pos).c_str());
    new_pos = i + 1;
}

Pin* line_to_pin(std::string s, char delim){
    int i = 0;
    std::replace(s.begin(), s.end(), ',', '.');
    float value;
    pop_front_number(s, delim, i, i, value);  // number of pin
    int number = (int)value;
    pop_front_number(s, delim, i, i, value);  // type of pin 1|2
    char type = (char)value;
    pop_front_number(s, delim, i, i, value);  // x
    int x = (int)(value * 10);
    pop_front_number(s, delim, i, i, value);  // y
    int y = (int)(value * 10);
    return new Pin(Point(y, x), number);
}

std::vector<Point*> read_pin_coordinates(std::string path_to_file){
    std::ifstream infile(path_to_file);
    std::string line;
    std::vector<Point*> pin_ptrs;
    while (std::getline(infile, line)) {
        pin_ptrs.push_back(line_to_pin(line, ';'));
    }
    return pin_ptrs;
}
