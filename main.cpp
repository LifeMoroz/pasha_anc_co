#include <vector>
#include <iostream>
#include <assert.h>
#include "utils.h"
#include "map.h"

bool test_pins(Map &map, std::vector<Point*> pins) {
    for (std::vector<Point*>::iterator it = pins.begin(); it != pins.end(); it++)
        assert(map.getPoint(**it)->type == MapPoint::pin);
    std::cerr << "Test pins ok!" << std::endl;
    return true;
}

int main() {
    std::vector<Point*> pins = read_pin_coordinates("C:\\Users\\Ruslan\\ClionProjects\\project\\coordinates.csv");
    Map map(200, 200);
    map.setPins(pins);
    test_pins(map, pins);
    map.findPath(*pins[0], *pins[41]);
    std::cerr << "Finished" << std::endl;
}