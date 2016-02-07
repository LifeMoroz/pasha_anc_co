#include <vector>
#include <iostream>
#include "utils.h"
#include "map.h"

int main() {
//Map map();
    std::vector<Point*> pins = read_pin_coordinates("C:\\Users\\Ruslan\\ClionProjects\\project\\coordinates.csv");
    Map map(10, 200, 200);
    map.setPins(pins);
    std::vector<Point*> points;
    for (int i = 1; i < 11; i++) {
        points.push_back(new Point(i,i,i));
    }
    Chain* new_chain = new Chain(points);
    map.setChain(new_chain);
    Point* m = new Pin(Point(), 1);
}