#include <fstream>
#include <algorithm>
#include <iostream>
#include "map.h"

void read_coordinates(){ // char*, Point**
    std::ifstream infile("C:\\Users\\Ruslan\\ClionProjects\\project\\coordinates.csv");
    std::string line;
    while (std::getline(infile, line)) {
        std::replace(line.begin(), line.end(), ';', ' ');
        std::cout << line << std::endl;
    }
}

int main() {
//Map map();
    read_coordinates();
}