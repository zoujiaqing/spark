#include "RadialGradient.h"
#include "PointF.h"

RadialGradient::RadialGradient(double cx0, double cy0, double radius0,
                               double cx1, double cy1, double radius1)
        :Gradient(cairo_pattern_create_radial(cx0,cy0,radius0,cx0,cy1,radius1))
{
}

RadialGradient::RadialGradient(const PointF& center0 ,double radius0,
                               const PointF& center1 ,double radius1)
        :Gradient(cairo_pattern_create_radial(center0.x,center0.y,radius0,
                                              center1.x,center1.y,radius1))
{
}

RadialGradient::~RadialGradient()
{
}
