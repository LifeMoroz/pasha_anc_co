#ifndef PROJECT_CHAIN_H
#define PROJECT_CHAIN_H
#include <vector>
#include "point.h"

class Chain {
public:
    Chain(std::vector<Point*>);
    std::vector<Point*> points;
};

#endif //PROJECT_CHAIN_H
