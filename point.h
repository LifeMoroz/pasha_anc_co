//
// Created by Ruslan on 07.02.2016.
//

#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H
#define pointType unsigned char
#define cordType int  // 0.1 мм
#define levelType unsigned char

class Point{
public:
    cordType x, y;
    levelType level;
    Point() {};
    Point(levelType, cordType, cordType);
};
#endif //PROJECT_POINT_H
