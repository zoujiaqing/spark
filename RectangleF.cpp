#include "RectangleF.h"
#include "PointF.h"

RectangleF::RectangleF()
{
    x = y = width = height = 0.0;
}

RectangleF::RectangleF(double X,double Y,double Width,double Height)
{
        x = X;
        y = Y;
        width = Width;
        height = Height;
}

PointF RectangleF::getOrigin() {
    PointF origin(x,y);
    return origin;
}
