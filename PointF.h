#ifndef POINTF_H
#define POINTF_H

class PointF
{
public:
    PointF();
    PointF(double X,double Y);
    bool operator<(const PointF& point);
    bool operator<=(const PointF& point);
    double x;
    double y;
};

#endif // POINTF_H
