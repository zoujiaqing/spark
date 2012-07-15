#ifndef PAINT_EVENT_H
#define PAINT_EVENT_H

#include "Event.h"

class Widget;
class Rectangle;
class Painter;
class Surface;

class PaintEvent : public Event
{
public:
    PaintEvent(Rectangle* clipRect,Rectangle* m_RedrawRect,Surface* surface);
    void init(Widget *widget,Rectangle* widgetRect,Rectangle* m_ParentRect);
    virtual Events::Type type();
private:
    friend class Painter;
    Widget* m_Widget;
    Rectangle* m_ClipRect;
    Rectangle* m_WidgetRect;
    Rectangle* m_RedrawRect;
    Rectangle* m_ParentRect;
    Surface *m_Surface;
};

#endif // PAINT_EVENT_H
