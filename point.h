//
// Created by Ruslan on 07.02.2016.
//

#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H
#define pointType int
#define cordType int  // 0.1 мм

class Point{
public:
    cordType x, y;
    Point() {};
    Point(const Point&);
    Point(cordType, cordType);

    friend bool operator== (Point &cP1, Point &cP2);

};
#endif //PROJECT_POINT_H
