#include <vector>
#include <iostream>
#include <assert.h>
#include "utils.h"
#include "map.h"
#include "Polygon.h"

bool test_pins(Map &map, std::vector<Point*> pins) {
    for (std::vector<Point*>::iterator it = pins.begin(); it != pins.end(); it++)
        assert(map.getPoint(**it)->type == MapPoint::pin);
    std::cerr << "Test pins ok!" << std::endl;
    return true;
}

bool test_chain(Map &map) {
    for (std::vector<Chain*>::iterator it_ch = map.chains.begin(); it_ch != map.chains.end(); it_ch++)
        for (std::vector<Point*>::iterator it = (*it_ch)->points.begin(); it != (*it_ch)->points.end(); it++) {
            std::cerr <<map.getPoint(**it)->type;
            assert(map.getPoint(**it)->type == MapPoint::chain);
        }
    std::cerr << "Test chain ok!" << std::endl;
    return true;
}

void test_polygons() {
    Polygon polygon;
    std::vector<Point *> points;
    points.push_back(new Point(1, 1));
    points.push_back(new Point(10, 1));
    polygon.writePolygon(points, 0);
}

int main() {
    test_polygons();
}