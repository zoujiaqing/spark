#ifndef SOLIDPATTERN_H
#define SOLIDPATTERN_H
#include "Pattern.h"

class Color;
class SolidPattern : public Pattern
{
public:
    SolidPattern(const Color& color);
    SolidPattern(double red,double green,double blue,double alpha = 1.0);
    ~SolidPattern();
};

#endif // SOLIDPATTERN_H
