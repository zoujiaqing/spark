#include "PaintEvent.h"

PaintEvent::PaintEvent(Rectangle* clipRect, Rectangle* redrawRect,Surface* surface)
                        :m_Widget(0),
                         m_WidgetRect(0),
                         m_ClipRect(clipRect),
                         m_RedrawRect(redrawRect),
                         m_ParentRect(0),
                         m_Surface(surface)
{

}

void PaintEvent::init(Widget *widget,Rectangle* widgetRect,
                       Rectangle* parentRect)
{
    m_Widget = widget;
    m_WidgetRect = widgetRect;
    m_ParentRect = parentRect;

}

Events::Type PaintEvent::type()
{
    return Events::Paint;
}

