//
// Created by Ruslan on 07.02.2016.
//

#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H
#define pointType int
#define cordType int  // 0.1 мм
#define levelType int

class Point{
public:
    cordType x, y;
    levelType level;
    Point() {};
    Point(const Point&);
    Point(levelType, cordType, cordType);

    friend bool operator== (Point &cP1, Point &cP2);
};
#endif //PROJECT_POINT_H
