#include "Gradient.h"
#include "Color.h"

Gradient::Gradient(cairo_pattern_t *pattern)
        :Pattern(pattern)
{
}

void Gradient::addColorStop(double offset,const Color & color)
{
    cairo_pattern_add_color_stop_rgba(m_CairoPattern,offset,color.r,color.g,color.b,color.a);
}

void Gradient::addColorStop(double offset,double red,double green,double blue,double alpha)
{
    cairo_pattern_add_color_stop_rgba(m_CairoPattern,offset,red,green,blue,alpha);
}

int Gradient::colorStopCount()
{
    int count;
    cairo_pattern_get_color_stop_count(m_CairoPattern,&count);
    return count;
}

Gradient::~Gradient()
{
}
