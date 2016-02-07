#include <algorithm>
#include "map.h"
#include <assert.h>
#include <iostream>

const pointType Map::empty = 0;
const pointType Map::chain = 1;
const pointType Map::pin = 2;

Map::Map(levelType z_size, cordType y_size, cordType x_size) {
    this->level_number = z_size;
    this->y_size = y_size;
    this->x_size = x_size;

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
    for (int z = 0; z < level_number; z++) {
        this->map[z] = new pointType *[y_size];
        for (int y = 0; y < y_size; y++)
            delete[] this->map[z][y];
        delete[] this->map[z];
    }
    delete[] this->map;
}

void Map::setPoint(levelType z, cordType y, cordType x, pointType value) {
    assert(this->isFree(z, y, x));
    assert(z > 0 && z <= this->level_number);  // z-1
    assert(y >= 0 && y < this->y_size);
    assert(x >= 0 && x < this->x_size);
    this->map[z-1][y][x] = value;
}

void Map::setPin(levelType z, cordType y, cordType x, pointType number) {
    this->setPoint(z, y, x, Map::pin);
    this->pins.push_back(new Pin(Point(z,y,x), number));
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

void Map::setChain(Chain* chain) {
    for(std::vector<Point*>::iterator it = chain->points.begin(); it != chain->points.end(); ++it)
        this->setChain(**it);
    this->chains.push_back(chain);
}

void Map::setPins(std::vector<Point*> points) {  // null-end array
    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        Point* point = *it;
        Pin pin = (Pin&)*point;
        this->setPin(pin);
    }
}
bool Map::isFree(levelType z, cordType y, cordType x) {
    assert(z >= 0 && z < this->level_number);
    assert(y >= 0 && y < this->y_size);
    assert(x >= 0 && x < this->x_size);
    return this->map[z-1][y][x] == Map::empty;
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
