#include <algorithm>
#include "map.h"
#include <assert.h>
#include <iostream>

const pointType MapPoint::empty = 0;
const pointType MapPoint::chain = -1;
const pointType MapPoint::pin = -2;

const int MapPoint::base_cost = 1;
const int MapPoint::base_cost_v = 10;

// Оптимизирующие параметры
const pointType Map::Lmin = 3;
const pointType Map::Vmin = 6;
const pointType Map::Smin = 50;

Map::Map(cordType y_size, cordType x_size) {
    this->y_size = y_size;
    this->x_size = x_size;
    this->max_lvl = 1;

    this->map = new MapPoint*[y_size];
    for (int y = 0; y < y_size; y++) {
        this->map[y] = new MapPoint[x_size];
        for (int x = 0; x < x_size; x++)
            this->map[y][x] = MapPoint(MapPoint::empty);
    }
}

Map::~Map() {
    for (int y = 0; y < y_size; y++)
        delete[] this->map[y];
    delete[] this->map;
}

void Map::setPointType(cordType y, cordType x, pointType type) {
    assert(this->isFree(y, x));
    assert(y >= -10 && y < this->y_size);
    assert(x >= -10 && x < this->x_size);
    this->map[y + 10][x + 10].type = type;
}

MapPoint Map::getPoint(cordType y, cordType x) {
    if ((y + 10 >= 0 && y + 10 < this->y_size) && (x + 10 >= 0 && x + 10 < this->x_size))
        return this->map[y + 10][x + 10];
    else
        return MapPoint(MapPoint::pin);
}

MapPoint Map::getPoint(Point point) {
    return this->getPoint(point.y, point.x);
}

void Map::setPin(cordType y, cordType x, pointType number) {
    this->setPointType(y, x, MapPoint::pin);
    this->pins.push_back(new Pin(Point(y,x), number));
}

void Map::setPin(Pin pin) {
    this->setPin(pin.y, pin.x, pin.number);
}

void Map::setChain(cordType y, cordType x) {
    this->setPointType(y, x, MapPoint::chain);
}

void Map::setChain(Point point) {
    this->setChain(point.y, point.x);
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

bool Map::isFree(cordType y, cordType x) {
    return this->getPoint(y, x).isFree();
}

bool Map::isFree(Point point) {
    return this->getPoint(point).isFree();
}

void Map::thin() {
    return;
}

int Map::cost(Point current, Point to) {
    // L/Lmin + V/(2*Vmin) + S/(3*Smin) -> min
    int i1 = this->max_lvl / this->Lmin;
    int i2 = (to.y - current.y) / this->Vmin;
    int i3 = (to.x - current.x) / this->Smin;
    return i1 + i2/2 + i3/3;
}

void Map::markNearlyPoints(std::vector<Point> &points, Point point, Point target) {
    // Окрестность Мура 3d
    Point* ps = new Point[6];
    ps[0] = Point(point.y, point.x);
    ps[1] = Point(point.y - 1, point.x);
    ps[2] = Point(point.y, point.x - 1);
    ps[3] = Point(point.y, point.x);
    ps[4] = Point(point.y + 1, point.x);
    ps[5] = Point(point.y, point.x + 1);

    for (char i=0; i < 6; i++)
        if (!this->getPoint(point).setChain()) {
            if (ps[i] == target) {
                int cost = this->getPoint(point).cost();
                if (this->finded_min_cost > cost)
                    this->finded_min_cost = cost;
            }
        }
        else {
            points.push_back(ps[i]);
        }
}

void Map::findPath(const Point from, const Point to) {
    std::vector<Point> points_to_mark;
    this->markNearlyPoints(points_to_mark, from, to);
    for (int i = 0; i < points_to_mark.size(); i++)
        this->markNearlyPoints(points_to_mark, points_to_mark[i], to);
    std::cout<<1;
}

MapPoint::MapPoint(pointType type) {
    this->count = 0;
    this->type = type;
};

bool MapPoint::setChain() {
    if (count >= 9 || type == MapPoint::pin)
        return false;
    this->count++;
    return true;
}

int MapPoint::cost() {
    return MapPoint::base_cost * count * 2 + MapPoint::base_cost_v * count;
}

MapPoint::MapPoint() {};

bool MapPoint::isFree() {
    return this->type == MapPoint::empty || this->type == MapPoint::chain;
}
