#include "pin.h"

Pin::Pin(Point *point, unsigned int number) {
    this->point = *point;
    this->number = number;
}
