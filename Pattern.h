#ifndef PATTERN_H
#define PATTERN_H
#include <cairo.h>

class Surface;
class Matrix;
class Painter;
namespace Extend
{
    enum Mode
    {
        Transparent = 0,
        Repeat,
        Reflect,
        Pad
    };
}

namespace Filter
{
    enum Type
    {
        Fast,
        Good,
        Best,
        Nearest,
        Bilinear
    };
}



class Pattern
{
public:

    virtual ~Pattern();
    cairo_pattern_t* getCairoPattern() const;
    Extend::Mode extend();
    void setExtend(Extend::Mode mode);
    Filter::Type filter();
    void setFilter(Filter::Type type);
    void setMatrix(Matrix& matrix);

protected:
    friend class Painter;
    Pattern(cairo_pattern_t *pattern);
    cairo_pattern_t *m_CairoPattern;
};

#endif // PATTERN_H
