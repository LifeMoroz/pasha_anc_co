#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include "global.h"
#include <vector>
#include "chain.h"
#include "point.h"
#include "pin.h"
class MapPoint{

    static const int base_cost;
    static const int base_cost_v;
    int count;
public:
    MapPoint();
    MapPoint(int type);

    static const pointType empty;
    static const pointType chain;
    static const pointType pin;

    bool setChain();
    int cost();
    bool isFree();

    int type;
};

class Map {
public:
// Оптимизующие параметры
    static const int Lmin;
    static const int Vmin;
    static const int Smin;

    Map(cordType, cordType);
    ~Map();
    void setPin(cordType, cordType, pointType);
    void setPin(Pin);
    void setChain(cordType, cordType);
    void setPins(std::vector<Point*>);  // null-end array
    void setChain(Chain*);

    MapPoint getPoint(Point);

    bool isFree(cordType, cordType);
    void thin();
    void findPath(const Point from, const Point to);

private:
    MapPoint** map;
    std::vector<Chain*> chains;
    std::vector<Pin*> pins;

    void setPointType(cordType, cordType, pointType);
    void setChain(Point point);

    cordType y_size;
    cordType x_size;


    int max_lvl;
    int max_v;
    int max_s;

    int finded_min_cost;

    int cost(Point current, Point to);
    bool isFree(Point point);
    void markNearlyPoints(std::vector<Point> &points, Point point, Point target);

    MapPoint getPoint(cordType, cordType);
};

#endif //PROJECT_MAP_H