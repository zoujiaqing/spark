#include "SolidPattern.h"
#include "Color.h"

SolidPattern::SolidPattern(const Color& color)
             :Pattern(cairo_pattern_create_rgba(color.r,color.g,color.b,color.a))
{

}

SolidPattern::SolidPattern(double red,double green,double blue,double alpha)
             :Pattern(cairo_pattern_create_rgba(red,green,blue,alpha))
{
}

SolidPattern::~SolidPattern()
{
}
