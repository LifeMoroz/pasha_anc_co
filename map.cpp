#include <algorithm>
#include "map.h"
#include <assert.h>
#include <iostream>

const pointType Map::empty = 0;
const pointType Map::chain = 1;
const pointType Map::pin = 2;

Map::Map(levelType z_size, cordType y_size, cordType x_size) {
    this->map = new pointType**[z_size];
    for (int z = 0; z < z_size; z++) {
        this->map[z] = new pointType*[y_size];
        for (int y = 0; y < y_size; y++) {
            this->map[z][y] = new pointType[x_size];
            for (int x = 0; x < x_size; x++)
                this->map[z][y][x] = Map::empty;
        }
    }
}

Map::~Map() {
}

void Map::setPoint(levelType z, cordType y, cordType x, pointType value) {
    assert(this->isFree(z, y, x));
    this->map[z][y][x] = value;
}

void Map::setPin(levelType z, cordType y, cordType x, pointType number) {
    this->setPoint(z, y, x, Map::pin + number);
}

void Map::setPin(Pin pin) {
    this->setPin(pin.level, pin.y, pin.x, pin.number);
}

void Map::setChain(levelType z, cordType y, cordType x) {
    this->setPoint(z, y, x, Map::chain);

}

void Map::setChain(Point point) {
    this->setChain(point.level, point.y, point.x);
}

void Map::setPins(std::vector<Point*> points) {  // null-end array
    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        Point* point = *it;
        Pin pin = (Pin&)*point;
    }
    std::copy(points.begin(), points.end(), std::back_inserter(this->pins));
}

void Map::setChains(std::vector<Point> points) {
    for(std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
        this->setChain(*it);
}

bool Map::isFree(levelType z, cordType y, cordType x) {
    return this->map[z][y][x] == Map::empty;
}

void Map::thin() {
    return;
}

pointType Map::getPoint(Point point) {
    return this->map[point.level][point.y][point.x];
}

Pin Map::getPin(Point point) {
    return Pin(point, this->getPoint(point));
}
