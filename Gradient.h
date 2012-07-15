#ifndef GRADIENT_H
#define GRADIENT_H
#include "Pattern.h"

class Color;
class Gradient : public Pattern
{
public:
    ~Gradient();
    void addColorStop(double offset,const Color & color);
    void addColorStop(double offset,double red,double green,double blue,double alpha = 1.0);
    int colorStopCount();
protected:
    Gradient(cairo_pattern_t *pattern);
};

#endif // GRADIENT_H
