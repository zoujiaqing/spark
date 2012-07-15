#include "NativeWindowSurface.h"
#include <cairo/cairo-xlib.h>

NativeWindowSurface::NativeWindowSurface(Display* display,Window window,Visual* visual,int width,int height)
{
    m_CairoSurface = cairo_xlib_surface_create (display,window,visual,width,height);
}

void NativeWindowSurface::setSize(Size size)
{
    cairo_xlib_surface_set_size(m_CairoSurface,size.width,size.height);
}
