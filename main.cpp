#include <vector>
#include <iostream>
#include "utils.h"
#include "map.h"

int main() {
//Map map();
    std::vector<Point*> pins = read_pin_coordinates("C:\\Users\\Ruslan\\ClionProjects\\project\\coordinates.csv");
    Map map(10, 200, 200);
    map.setPins(pins);
    Point* m = new Pin(Point(), 1);
}