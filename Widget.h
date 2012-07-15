#ifndef WIDGET_H
#define WIDGET_H 1

#include "sigslot.h"
#include "WindowSystem.h"
#include "Color.h"
#include "Size.h"
#include "Point.h"
#include "Events.h"
#include <X11/Xlib.h>
#include <cairo/cairo.h>
#include <list>


class Surface;

typedef Window NativeWindow;

namespace WidgetFlags
{
    enum Flag
    {
      NotSizeable   = 1,
      FlexWidth     = 2,
      FlexHeight    = 4,
      MoveLeft      = 8,
      MoveRight     = 16,
      MoveTop       = 32,
      MoveBottom    = 64
    };
}

class Widget {

public:

    Widget(Widget *parentWidget ,int x,int y,int width,int height,int flags = 0);
    virtual ~Widget();

    const int x() { return m_Origin.x; }
    const int y() { return m_Origin.y; }
    const int width() { return m_Size.width; }
    const int height() { return m_Size.height; }

    const Size size() { return m_Size; }
    const Point origin() { return m_Origin; }

    void show();
    void hide();
    void move(Point toPosition);
    bool isVisible();
    void getFocus();
    void toTop();
    void toBottom();
    void stackAbove(Widget *sibling);
    void stackBelow(Widget *sibling);
    void resize(int width,int height);
    void resize(Size *size);
    void update();
    void update(double x0,double y0,double x1,double y1);
    void update(const Rectangle clipRect);


    virtual bool handleEvent(Event * event);
    virtual void onPaintEvent(PaintEvent * event);
    virtual bool onMouseEvent(MouseEvent * event);
    virtual bool onKeyPressEvent(KeyEvent *event);
    virtual bool onKeyReleaseEvent(KeyEvent *event);
    virtual void onResizeEvent(ResizeEvent *event);
    virtual void onFocusEvent(FocusEvent *event);

    Widget* childAt(int x,int y);


    void setBackground(double r,double g,double b,double a = 1.0);
    void setBackground(const Color &color);
    const Color& backgroundColor(){ return m_BackgroundColor;}

protected:
    friend class Painter;
    friend class WindowSystem;

    NativeWindow m_NativeWindowID;
    bool m_IsTopLevel;
    bool m_IsNative;
    bool m_IsVisible;
    Widget* m_ParentWidget;
    std::list<Widget *> m_Children;
    Surface* m_CairoSurface;
    Surface* m_NativeWindowSurface;
    Color m_BackgroundColor;
    Point m_Origin;
    Size m_Size;



};
#endif
