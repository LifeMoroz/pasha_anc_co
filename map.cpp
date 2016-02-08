#include <algorithm>
#include "map.h"
#include <assert.h>
#include <iostream>

const pointType MapPoint::empty = 0;
const pointType MapPoint::chain = -1;
const pointType MapPoint::pin = -2;
const pointType MapPoint::connect = -3;

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
    Point* ps = this->getAdjacentFNPoints(*new_pin);
    for (int i = 0; i < 8; i++) {
        this->getPoint(ps[i])->type = MapPoint::connect; // Попдадаю сюда нарушает в 80% случаев правило отступа
    }
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

Point* Map::getAdjacentMurPoints(Point &point) {
    /* Returns always 4 related points. Doesnt validate it */
    Point * ps = new Point[4];
    ps[0] = Point(point.y - 1, point.x);
    ps[1] = Point(point.y, point.x - 1);
    ps[2] = Point(point.y + 1, point.x);
    ps[3] = Point(point.y, point.x + 1);

    return ps;
}


Point* Map::getAdjacentFNPoints(Point &point) {
    /* Returns always 8 related points. Doesnt validate it */
    Point * ps = new Point[8];
    ps[0] = Point(point.y - 1, point.x);
    ps[1] = Point(point.y, point.x - 1);
    ps[2] = Point(point.y + 1, point.x);
    ps[3] = Point(point.y, point.x + 1);
    ps[4] = Point(point.y - 1, point.x - 1);
    ps[5] = Point(point.y - 1, point.x + 1);
    ps[6] = Point(point.y + 1, point.x - 1);
    ps[7] = Point(point.y + 1, point.x + 1);
    return ps;
}

void Map::markAdjacentPoints(std::vector<Point> &points, Point point) {
    // Окрестность Мура -> 4 элемента
    Point* ps = this->getAdjacentMurPoints(point);
    MapPoint* map_point = this->getPoint(point);
    for (char i=0; i < 4; i++) {
        MapPoint *p = this->getPoint(ps[i]);
        if (p != NULL && p->set(map_point->cost_path) && this->getPoint(ps[i])->type != MapPoint::pin)
            points.push_back(Point(ps[i]));
    }
    delete [] ps;
}

void Map::findPath(Point from, Point to) {
    std::cout << "From: " << from.y << " " << from.x << std::endl;
    std::cout << "To: " << to.y << " " << to.x << std::endl;
    // Заполняем карту волнами
    std::vector<Point> points_to_mark;
    this->markAdjacentPoints(points_to_mark, from);
    for (int i = 0; i < points_to_mark.size(); i++)
        this->markAdjacentPoints(points_to_mark, points_to_mark[i]);
    points_to_mark.clear();  // Нам больше не нужен
    // Идем обратно, составляем путь
    std::vector<Point*> chain_points;
    Point point = to;
    chain_points.push_back(new Point(to));
    Point* ps;
    char min_i = 0;  // вообще конечно ломает немножко
    while (point != from) {
        ps = this->getAdjacentMurPoints(point);
        min_i = 0;
        MapPoint* map_point;
        MapPoint* min_related;
        for (char i = 0; i < 4; i++) {
            map_point = this->getPoint(ps[i]);
            min_related = this->getPoint(ps[min_i]);
            if (map_point != NULL && map_point->type != MapPoint::pin && (map_point->type != MapPoint::connect or point == to)) {
                if (min_related == NULL || map_point->cost_path < min_related->cost_path
                        || min_related->type == MapPoint::pin || min_related->type == MapPoint::connect) {
                    min_i = i;
                }
            }
            else if (ps[i] == from) {
                chain_points.push_back(new Point(ps[i]));
                point = *chain_points.back();
                delete[] ps;
                this->chains.push_back(new Chain(chain_points));
                for (std::vector<Point *>::iterator it_ch = this->chains.back()->points.begin();
                     it_ch != this->chains.back()->points.end(); it_ch++)
                    this->getPoint(**it_ch)->setChain();
                return;
            }
            else if (map_point->type == MapPoint::connect) { //проходим растояния отступа
                Point *related_points = this->getAdjacentMurPoints(ps[i]);
                for (int k = 0; k < 4; k ++)
                    if (related_points[k] == from) {
                        chain_points.push_back(new Point(ps[i]));
                        delete [] related_points;
                        chain_points.push_back(new Point(from));
                        this->chains.push_back(new Chain(chain_points));
                        for (std::vector<Point *>::iterator it_ch = this->chains.back()->points.begin();
                                 it_ch != this->chains.back()->points.end(); it_ch++)
                            this->getPoint(**it_ch)->setChain();
                        return;
                    }
            }
        }
        std::cout<<ps[min_i].x << " " << ps[min_i].y<< " " << min_related->cost_path << std::endl;
        chain_points.push_back(new Point(ps[min_i]));
        point = *chain_points.back();
        delete [] ps;
    }
}

MapPoint::MapPoint(pointType type) {
    this->count = 0;
    this->type = type;
    this->cost_path = 999999;
};

bool MapPoint::setPin(Pin* pin) {
    this->count = 0;
    this->type = MapPoint::pin;
    this->related = pin;
    this->cost_path = 0;
    return true;
}

bool MapPoint::setChain() {
    if (this->type == MapPoint::pin)
        return false;
    this->count++;
    this->type = MapPoint::chain;
    return true;
}

bool MapPoint::set(int cost) {
    if (this->type == MapPoint::pin)
        return false;
    if(this->cost_path > (cost + this->cost())) // Сюда можно добраться дешевле
        this->cost_path = cost + this->cost();
    else
        return false;
    return true;
}

int MapPoint::cost() {
    return 1 + 10 * this->count;
}

MapPoint::MapPoint() {};

