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
    void* related;
public:
    MapPoint();
    MapPoint(int type);

    static const pointType empty;
    static const pointType chain;
    static const pointType pin;
    static const pointType connect;

    bool setChain();
    int cost();
    bool isFree();

    int type;
    int cost_path;

    bool set(int cost);

    bool setPin(Pin* pin);

    int count;
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
    void setPins(std::vector<Point*>);  // null-end array

    MapPoint* getPoint(Point);
    MapPoint* getPoint(cordType, cordType);

    void findPath(const Point from, const Point to);

    std::vector<Chain*> chains;
private:
    MapPoint** map;
    std::vector<Pin*> pins;

    cordType y_size;
    cordType x_size;

    void markAdjacentPoints(std::vector<Point> &points, Point point);

    Point *getAdjacentPoints(Point &point);
};

#endif //PROJECT_MAP_H