#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include "global.h"
#include <vector>
#include "chain.h"
#include "point.h"
#include "pin.h"


class Map {
public:
    static const pointType empty;
    static const pointType chain;
    static const pointType pin;

    Map(levelType, cordType, cordType);
    ~Map();
    void setPin(levelType, cordType, cordType, pointType);
    void setPin(Pin);
    void setChain(levelType, cordType, cordType);
    void setPins(std::vector<Point*>);  // null-end array
    void setChain(Chain*);

    pointType getPoint(Point);
    Pin getPin(Point);

    bool isFree(levelType, cordType, cordType);
    void thin();

private:
    pointType*** map;
    std::vector<Chain*> chains;
    std::vector<Pin*> pins;

    void setPoint(levelType, cordType, cordType, pointType);
    void setChain(Point point);

    levelType level_number;
    cordType y_size;
    cordType x_size;
};

#endif //PROJECT_MAP_H