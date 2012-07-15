#include "LinearGradient.h"
#include "PointF.h"
LinearGradient::LinearGradient(double x0,double y0,double x1,double y1)
        :Gradient(cairo_pattern_create_linear(x0,y0,x1,y1))
{
}

LinearGradient::LinearGradient(PointF &start,PointF &stop)
        :Gradient(cairo_pattern_create_linear(start.x,start.y,stop.x,stop.y))
{
}

LinearGradient::~LinearGradient()
{
}
