#include "Pattern.h"
#include "Matrix.h"
Pattern::Pattern(cairo_pattern_t* pattern):m_CairoPattern(pattern)
{

}

Pattern::~Pattern()
{
    if(m_CairoPattern) cairo_pattern_destroy(m_CairoPattern);
}

cairo_pattern_t* Pattern::getCairoPattern() const
{
    return m_CairoPattern;
}


Extend::Mode Pattern::extend()
{
    return (Extend::Mode) cairo_pattern_get_extend(m_CairoPattern);
}

void Pattern::setExtend(Extend::Mode mode)
{
    cairo_pattern_set_extend(m_CairoPattern,(cairo_extend_t) mode);
}

Filter::Type Pattern::filter()
{
    return (Filter::Type) cairo_pattern_get_filter(m_CairoPattern);
}

void Pattern::setFilter(Filter::Type type)
{
    cairo_pattern_set_filter(m_CairoPattern,(cairo_filter_t) type);
}

void Pattern::setMatrix(Matrix& matrix)
{
    cairo_pattern_set_matrix(m_CairoPattern,matrix.getCairoMatrix());
}
