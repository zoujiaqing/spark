#include "SurfacePattern.h"
#include "Surface.h"
SurfacePattern::SurfacePattern(Surface* surface)
               :Pattern(cairo_pattern_create_for_surface(surface->getCairoSurface()))
{

}
SurfacePattern::~SurfacePattern()
{
}
