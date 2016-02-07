//
// Created by ivan on 07.02.16.
//

#include "Polygon.h"
#include <fstream>
#include <iostream>

//уравнение прямой: (y1-y2)*x + (x2-x1)*y + (x1*y2 - x2*y1) = 0

void Polygon::writePolygon(std::vector<Point *> points, int numberOfLayers) {
    for(int i = 0; i < points.size() - 1; i++) {
        PolygonPoint* qwe = findPoint(points[i], points[i+1]);
        for(int j = 0; j < 4; j++) {
            std::cout << qwe[j].x << "  " << qwe[j].y << std::endl;
        }
    }
}

PolygonPoint* Polygon::findPoint(Point* first, Point* second) {
    float A = ((*second).y - (*first).y),
            B = ((*first).x - (*second).x),
            C = -(*first).x *((*second).y - (*first).y) + (*first).y * ((*second).x - (*first).x); //исходная прямая
    float C1 = A * (*first).y - B * (*first).x; // константа первого перпендикуляра
    float C2 = A * (*second).y - B * (*second).x; // константа второго перпендикуляра

    PolygonPoint* points = new PolygonPoint[4];

    std::cout << "A = " << A << "  " << "B = " << B << "  " << "C = " << C << "  " << "C1 = " << C1 << "  " << "C2 = " << C2 << "  " << std::endl;
    //вычисление 4 угловых точек полигона. 0 и 1 - точки возле начала, 2 и 3 - возле конца отрезка
    for(int i = 0; i < 4; i++) {
        float delta = 0.5, C0 = C1;
        if(i == 1 || i == 3) delta *= -1;
        if(i > 1) C0 = C2;
        //points[i].y = -1 * (B * C0 + A * (C + delta)) / (A * A + B * B);
        points[i].y =  (C0 * A - (C + delta) * B) / (B * B + A * A);
        points[i].x = (B * points[i].y + C0) / A;
    }

    return points;
}
