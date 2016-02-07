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

bool test_chain(Map &map) {
    for (std::vector<Chain *>::iterator it_ch = map.chains.begin(); it_ch != map.chains.end(); it_ch++) {
        for (std::vector<Point *>::iterator it = (*it_ch)->points.begin(); it != (*it_ch)->points.end(); it++) {
            std::cerr << (**it).x << " " << (**it).y << " " << map.getPoint(**it)->type << std::endl;
            if (it == (*it_ch)->points.begin() || it == (*it_ch)->points.end())
                assert(map.getPoint(**it)->type == MapPoint::pin);
            else {
                if (map.getPoint(**it)->type != MapPoint::chain) {}
                   // std::cout << e << std::endl;
            }
        }
        std::cerr << "Test 1 chain ok!" << std::endl;
    }
    std::cerr << "Test chain ok!" << std::endl;
    return true;
}


int main() {
    std::vector<Point*> pins = read_pin_coordinates("C:\\Users\\Ruslan\\ClionProjects\\project\\coordinates.csv");
    Map map(210, 210);
    map.setPins(pins);
    test_pins(map, pins);
    map.findPath(*pins[0], *pins[41]);
    test_chain(map);
    map.findPath(*pins[1], *pins[42]);
    test_chain(map);
    std::cout << map.getPoint(*map.chains[0]->points[5])->count << std::endl;
    std::cerr << "Finished" << std::endl;
}