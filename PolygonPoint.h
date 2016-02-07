//
// Created by ivan on 08.02.16.
//

#ifndef PROJECT_POLYGONPOINT_H
#define PROJECT_POLYGONPOINT_H
#define cordType double  // 0.1 мм

class PolygonPoint {
public:
    cordType x, y;
    PolygonPoint() {};
    PolygonPoint(const PolygonPoint&);
    PolygonPoint(cordType, cordType);
};


#endif //PROJECT_POLYGONPOINT_H
