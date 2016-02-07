#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H
#include <vector>
#include "chain.h"
#include "point.h"


class Map {
public:
    static const pointType empty;
    static const pointType chain;
    static const pointType pin;

    Map(levelType, cordType, cordType);
    ~Map();
    void setPin(levelType, cordType, cordType);
    void setPin(Point);
    void setChain(levelType, cordType, cordType);
    void setChain(Point point);
    void setPins(std::vector<Point>);  // null-end array
    void setChains(std::vector<Point>);

    bool isFree(levelType, cordType, cordType);
    void thin();

private:
    pointType*** map;
    std::vector<Chain*> chains;

    void setPoint(levelType, cordType, cordType, pointType);
};

#endif //PROJECT_MAP_H