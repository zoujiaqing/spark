#ifndef NATIVEWINDOWSURFACE_H
#define NATIVEWINDOWSURFACE_H
#include "Surface.h"
#include "WindowSystem.h"
#include "Size.h"

class NativeWindowSurface : public Surface
{
protected:
    friend class WindowSystem;
    NativeWindowSurface(Display* display,Window window,Visual* visual,int width,int height);
    void setSize(Size size);

};

#endif // NATIVEWINDOWSURFACE_H
