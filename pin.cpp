#include "pin.h"

Pin::Pin(Point point, unsigned int number): Point(point) {
    this->number = number;
}
