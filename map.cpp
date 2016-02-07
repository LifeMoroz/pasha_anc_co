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

MapPoint* Map::getPoint(cordType y, cordType x) {
    if ((y + 10 >= 0 && y + 10 < this->y_size) && (x + 10 >= 0 && x + 10 < this->x_size))
        return &this->map[y + 10][x + 10];
    else
        return NULL;
}

MapPoint* Map::getPoint(const Point point) {
    return this->getPoint(point.y, point.x);
}

void Map::setPin(cordType y, cordType x, pointType number) {
    Pin* new_pin = (new Pin(Point(y,x), number));
    MapPoint* mp = this->getPoint(y, x);
    mp->setPin(new_pin);
    this->pins.push_back(new_pin);
}

void Map::setPin(Pin pin) {
    this->setPin(pin.y, pin.x, pin.number);
}

void Map::setPins(std::vector<Point*> points) {  // null-end array
    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        Point* point = *it;
        Pin pin = (Pin&)*point;
        this->setPin(pin);
    }
}

bool Map::isFree(cordType y, cordType x) {
    return this->getPoint(y, x)->isFree();
}

Point Map::getAdjacentPoints() {

}

void Map::markAdjacentPoints(std::vector<Point> &points, Point point) {
    // Окрестность Мура
    Point ps[4];

    ps[0] = Point(point.y - 1, point.x);
    ps[1] = Point(point.y, point.x - 1);
    ps[2] = Point(point.y + 1, point.x);
    ps[3] = Point(point.y, point.x + 1);

    MapPoint* map_point = this->getPoint(point);
    for (char i=0; i < 4; i++) {
        MapPoint *p = this->getPoint(ps[i]);
        if (p != NULL && p->set(map_point->cost_path) && this->getPoint(ps[i])->type != MapPoint::pin)
            points.push_back(ps[i]);
    }
}

void Map::findPath(const Point from, const Point to) {
    std::cout << "From: " << from.y << " " << from.x << std::endl;
    std::cout << "To: " << to.y << " " << to.x << std::endl;
    // Заполняем карту волнами
    std::vector<Point> points_to_mark;
    this->markAdjacentPoints(points_to_mark, from);
    for (int i = 0; i < points_to_mark.size(); i++)
        this->markAdjacentPoints(points_to_mark, points_to_mark[i]);
    points_to_mark.clear();  // Нам больше не нужен
    // Идем обратно, составляем путь
    std::cout << this->map[65][151].cost_path << std::endl;
    std::cout << this->map[65][149].cost_path << std::endl;
    std::cout << this->map[64][150].cost_path << std::endl;
    std::cout << this->map[66][150].cost_path << std::endl;
}

MapPoint::MapPoint(pointType type) {
    this->count = 0;
    this->type = type;
};

bool MapPoint::setPin(Pin* pin) {
    this->type = MapPoint::pin;
    this->related = pin;
    this->cost_path = 0;
    return true;
}

bool MapPoint::setChain() {
    this->count++;
    return true;
}

bool MapPoint::set(int cost) {
    if (this->type == MapPoint::pin)
        return false;
    this->type = MapPoint::chain;
    if(this->cost_path > cost + 1) // Сюда можно добраться дешевле
        this->cost_path = cost + 1;
    else
        return false;
    return true;
}

int MapPoint::cost() {
    return MapPoint::base_cost * count * 2 + MapPoint::base_cost_v * count;
}

MapPoint::MapPoint() {};

bool MapPoint::isFree() {
    return this->type == MapPoint::empty || this->type == MapPoint::chain;
}
