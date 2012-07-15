#ifndef RADIALGRADIENT_H
#define RADIALGRADIENT_H
#include "Gradient.h"
class PointF;
class RadialGradient : public Gradient
{
public:
    RadialGradient(double cx0, double cy0, double radius0,
                   double cx1, double cy1, double radius1);

    RadialGradient(const PointF& center0 ,double radius0,
                   const PointF& center1 ,double radius1);

    ~RadialGradient();
};

#endif // RADIALGRADIENT_H
