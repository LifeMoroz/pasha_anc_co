//
// Created by Ruslan on 07.02.2016.
//

#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H
#define pointType unsigned char
#define cordType int  // 0.1 мм
#define levelType unsigned char

struct Point{
    cordType x, y;
    levelType level;
};
#endif //PROJECT_POINT_H
