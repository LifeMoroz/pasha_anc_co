//
// Created by ivan on 07.02.16.
//

#ifndef PROJECT_POLYGON_H
#define PROJECT_POLYGON_H

//Работает с Vector* point (точки представляют собой точки излома прямой)
//Минимальная ширина линии 0,1 мм => 0,05 по сторонам
/*Формат выходного файла:
    POLY <points_count>, <layer>, <point_1_x>, <point_1_y>, ..., <point_points_count_x>, <point_points_count_y>

    POLY — ключевое слово, означающее начало нового полигона.
    <points_count> — количество углов полигона.
    <layer> — номер слоя, на котором расположен полигон. Слои нумеруются от 1 (верхний слой) до 10 (нижний слой).
    <point_points_count_x>, <point_points_count_y> — координаты углов полигона,
        данные последовательно в произвольном направлении обхода (по или против часовой стрелки),
        заданные в мм, разделитель дробной части - запятая.

    JUMP <x> <y>

    <x>, <y> — координаты центра перехода (так называемого переходногоотверстия).

 */
#include "point.h"
#include "vector"
#include "string"
#include "PolygonPoint.h"

//
class Polygon {
public:
    void writePolygon(std::vector<Point*> points, int numberOfLayers);

private:
    const std::string filename = "out";
    PolygonPoint* findPoint(Point* first, Point* second);
};


#endif //PROJECT_POLYGON_H
