#ifndef LINEARGRADIENT_H
#define LINEARGRADIENT_H
#include "Gradient.h"
class PointF;
class LinearGradient : public Gradient
{
public:
    LinearGradient(double x0,double y0,double x1,double y1);
    ~LinearGradient();
    LinearGradient(PointF &start,PointF &stop);
};

#endif // LINEARGRADIENT_H
