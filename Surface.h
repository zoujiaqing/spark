#ifndef SURFACE_H
#define SURFACE_H
#include <cairo/cairo.h>

class Painter;
class WindowSystem;
class SurfacePattern;

class Surface
{
public:
    Surface();
    virtual ~Surface();
protected:
    friend class Painter;
    friend class WindowSystem;
    friend class SurfacePattern;
    Surface(cairo_surface_t* cairoSurface);
    cairo_surface_t* m_CairoSurface;
    cairo_surface_t* getCairoSurface();

};

#endif // SURFACE_H
