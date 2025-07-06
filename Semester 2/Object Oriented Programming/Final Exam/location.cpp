#include "location.h"

Location::Location(double x, double y) : x(x), y(y) {}

double Location::getX() {
    return x;
}

double Location::getY() {
    return y;
}