#include "Surface.h"

Surface::Surface()
{
}


Surface::~Surface()
{
    if (m_CairoSurface) cairo_surface_destroy(m_CairoSurface);
}


cairo_surface_t* Surface::getCairoSurface()
{
    return m_CairoSurface;
}

Surface::Surface(cairo_surface_t* cairoSurface)
{
    m_CairoSurface = cairoSurface;
    cairo_surface_reference(cairoSurface);
}
