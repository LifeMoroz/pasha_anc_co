#include <algorithm>
#include "global.h"
#include "map.h"
#include <assert.h>

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
    assert(value == Map::chain || value == Map::pin || value == Map::empty);
    assert(this->isFree(z, y, x));
    this->map[z][y][x] = value;
}

void Map::setPin(levelType z, cordType y, cordType x) {
    this->setPoint(z, y, x, Map::pin);
}

void Map::setPin(Point point) {
    this->setPin(point.level, point.y, point.x);
}

void Map::setChain(levelType z, cordType y, cordType x) {
    this->setPoint(z, y, x, Map::chain);

}

void Map::setChain(Point point) {
    this->setChain(point.level, point.y, point.x);
}

void Map::setPins(std::vector<Point> points) {  // null-end array
    for(std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
        this->setPin(*it);
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
