#ifndef RECTANGLEF_H
#define RECTANGLEF_H

class PointF;
class RectangleF
{
public:
    RectangleF();
    RectangleF(double  X,double Y,double Width,double Height);
    PointF getOrigin();
    double x;
    double y;
    double width;
    double height;
};

#endif // RECTANGLEF_H
