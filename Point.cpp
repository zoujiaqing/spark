#include "Point.h"

Point::Point(int X , int Y) {
    x = X;
    y = Y;
}
Point::Point() {
    x = 0;
    y = 0;
}
bool Point::operator<(const Point& point)
{

    return (x < point.x && y < point.y);
}

bool Point::operator<=(const Point& point)
{

    return (x <= point.x && y <= point.y);
}
