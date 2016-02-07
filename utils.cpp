//
// Created by Ruslan on 07.02.2016.
//
#include <stdlib.h>
#include <fstream>
#include <assert.h>
#include <vector>
#include "utils.h"
#include "pin.h"

void pop_front_number(std::string s, char delim, int pos, int &new_pos, float &value) {
    int i = s.find_first_of(delim, pos);
    new_pos = i;
    if (i!=-1) {
        value = atof(s.substr(0, i).c_str());
    }
    else
        value = atof(s.c_str());
}

Pin line_to_pin(std::string &s, char delim){
    int i = 0, k = 0;
    float value;
    pop_front_number(s, delim, i, k, value);  // number of pin
    int number = (int)value;
    pop_front_number(s, delim, i, k, value);  // type of pin 1|2
    char type = (char)value;
    pop_front_number(s, delim, i, k, value);  // x
    int x = (int)(value * 10);
    pop_front_number(s, delim, i, k, value);  // y
    int y = (int)(value * 10);
    return Pin(new Point(1,y,x), number);
}

std::vector<Pin> read_pin_coordinates(std::string path_to_file){
    std::ifstream infile(path_to_file);
    std::string line;
    std::vector<Pin> pin_ptrs;
    while (std::getline(infile, line)) {
        pin_ptrs.push_back(line_to_pin(line, ';'));
    }
    return pin_ptrs;
}
