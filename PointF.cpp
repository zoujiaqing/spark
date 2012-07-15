#include "PointF.h"

PointF::PointF(double X , double Y) {
    x = X;
    y = Y;
}
PointF::PointF() {
    x = 0.0;
    y = 0.0;
}
bool PointF::operator<(const PointF& point)
{

    return (x < point.x && y < point.y);
}

bool PointF::operator<=(const PointF& point)
{

    return (x <= point.x && y <= point.y);
}
