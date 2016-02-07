#include <vector>
#include <iostream>
#include "utils.h"
#include "map.h"

int main() {
//Map map();
    std::vector<Point*> pins = read_pin_coordinates("C:\\Users\\Ruslan\\ClionProjects\\project\\coordinates.csv");
    Map map(10, 20, 20);
    Point* m = new Pin(Point(), 1);
    map.setPins(pins);
}