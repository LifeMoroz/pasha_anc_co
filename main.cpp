#include <vector>
#include <iostream>
#include "utils.h"
#include "map.h"

int main() {
    std::vector<Point*> pins = read_pin_coordinates("C:\\Users\\Ruslan\\ClionProjects\\project\\coordinates.csv");
    Map map(200, 200);
    map.setPins(pins);
    std::vector<Point*> points;
    for (int i = 1; i < 11; i++) {
        points.push_back(new Point(i,i));
    }
    map.findPath(*pins[0], *pins[41]);
}