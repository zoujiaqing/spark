#include "Painter.h" 
#include "Application.h"
#include "Color.h"
#include "WindowSystem.h"
#include "Surface.h"
#include "Pattern.h"
#include "Point.h"
#include "PointF.h"
#include "Rectangle.h"
#include "RectangleF.h"
#include "AreaF.h"
#include "Widget.h"
#include "PaintEvent.h"
#include <cstdio>

Painter::Painter(PaintEvent *event)
{

    Widget *widget = event->m_Widget;
    Widget *rootWidget =  windowSystem->getToplevelParent(widget);


    if(! widget->m_IsTopLevel) {

        Point origin;
        windowSystem->getOriginRelativeToAncestor(widget,rootWidget,origin);

        cr = cairo_create(event->m_Surface->getCairoSurface());

        setClip(*event->m_ParentRect);
        setClip(*event->m_WidgetRect);
        setClip(*event->m_RedrawRect);
        setClip(*event->m_ClipRect);

        //clearRect();

        cairo_translate(cr,origin.x,origin.y);

    } else {

        cr = cairo_create(widget->m_CairoSurface->getCairoSurface());

        setClip(*event->m_WidgetRect);
        setClip(*event->m_RedrawRect);
        setClip(*event->m_ClipRect);

        clearRect();

    }
}

Painter::Painter(Surface *surface)
{
    if (surface)
    {
        cr = cairo_create(surface->getCairoSurface());
    }
}

Painter::~Painter()
{
    cairo_destroy(cr);
}
void Painter::setAntialiasing(bool yes)
{
    if(yes)
    {
        cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);
    }
    else
    {
        cairo_set_antialias (cr, CAIRO_ANTIALIAS_NONE);
    }
}

void Painter::setSource(const Color &color)
{
    cairo_set_source_rgba(cr,color.r,color.g,color.b,color.a);
}

void Painter::setSource(const Pattern &pattern)
{
    cairo_set_source(cr,pattern.getCairoPattern());
}

void Painter::setSource(Surface *surface,double x, double y)
{
    cairo_set_source_surface(cr,surface->getCairoSurface(),x,y);
}

void Painter::fill()
{
    cairo_fill(cr);
}

void Painter::fillPreserve()
{
    cairo_fill_preserve(cr);
}

void Painter::fillExtents(AreaF& area)
{
    cairo_fill_extents(cr,&area.left,&area.top,&area.right,&area.bottom);
}

bool Painter::inFill(PointF& point)
{
    return cairo_in_fill(cr,point.x,point.y);
}

void Painter::mask(Pattern& pattern)
{
    cairo_mask(cr,pattern.getCairoPattern());
}

void Painter::mask(Surface *surface, double x, double y)
{
    cairo_mask_surface(cr,surface->getCairoSurface(),x,y);
}

void Painter::paint()
{
    cairo_paint(cr);
}

void Painter::paint(double alpha)
{
    cairo_paint_with_alpha(cr,alpha);
}

void Painter::stroke()
{
    cairo_stroke(cr);
}

void Painter::strokePreserve()
{
    cairo_stroke_preserve(cr);
}

void Painter::strokeExtents(AreaF &area)
{
    cairo_stroke_extents(cr,&area.left,&area.top,&area.right,&area.bottom);
}

bool Painter::inStroke(PointF& point)
{
    return cairo_in_stroke(cr,point.x,point.y);
}

void Painter::pushGroup()
{
    cairo_push_group(cr);
}

Pattern* Painter::popGroup()
{
    return new Pattern(cairo_pop_group(cr));
}

void Painter::popGroupToSource()
{
    cairo_pop_group_to_source(cr);
}

Surface* Painter::groupTarget()
{
    return new Surface(cairo_get_group_target(cr));
}

FillRules::Rule Painter::fillRule()
{
    return (FillRules::Rule) cairo_get_fill_rule(cr);
}

void Painter::setFillRule(FillRules::Rule rule)
{
    cairo_set_fill_rule(cr,(cairo_fill_rule_t)rule);
}

LineCap::Type Painter::lineCap()
{
    return (LineCap::Type) cairo_get_line_cap(cr);
}

void Painter::setLineCap(LineCap::Type type)
{
    cairo_set_line_cap(cr,(cairo_line_cap_t)type);
}

LineJoin::Type Painter::lineJoin()
{
    return (LineJoin::Type)cairo_get_line_join(cr);
}

void Painter::setLineJoin(LineJoin::Type type)
{
    cairo_set_line_join(cr,(cairo_line_join_t)type);
}

double Painter::lineWidth()
{
    return cairo_get_line_width(cr);
}

void Painter::setLineWidth(double width)
{
    cairo_set_line_width(cr,width);
}

double Painter::miterLimit()
{
    return cairo_get_miter_limit(cr);
}

void Painter::setMiterLimit(double limit)
{
    cairo_set_miter_limit(cr,limit);
}

Operators::Type Painter::operatorType()
{
    return (Operators::Type) cairo_get_operator(cr);
}

void Painter::setOperator(Operators::Type type)
{
    cairo_set_operator(cr,(cairo_operator_t)type);
}

double Painter::tolerance()
{
    return cairo_get_tolerance(cr);
}

void Painter::setTolerance(double tolerance)
{
    cairo_set_tolerance(cr,tolerance);
}

void Painter::copySurface(Surface *surface,int x, int y)
{
    cairo_save(cr);
    cairo_set_source_surface(cr,surface->getCairoSurface(),x,y);
    cairo_set_operator(cr,CAIRO_OPERATOR_SOURCE);
    cairo_paint(cr);
    cairo_restore(cr);

}

void Painter::fillRect(double r, double g,double b,double a)
{
    cairo_set_source_rgba(cr, r, g, b, a);
    cairo_paint (cr);
    return;	
}

void Painter::fillRect(const Color &color)
{
    cairo_set_source_rgba(cr, color.r, color.g, color.b,color.a);	
    cairo_paint (cr);
    return;
}

void Painter::setClip(Rectangle& clipRectangle)
{
    cairo_rectangle(cr,clipRectangle.x,clipRectangle.y,clipRectangle.width,clipRectangle.height);
    cairo_clip(cr);

    return;
	
}
void Painter::resetClip()
{
    cairo_reset_clip(cr);
    return;

}
void Painter::drawRoundedRect(double x,double y,double width,double height,double radius)
{

    double degrees = 3.14285714285714285714 / 180.0;

    cairo_new_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees,0.0);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0.0, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);

    //cairo_clip(cr);

    //cairo_stroke_preserve (cr);
    //cairo_paint (cr);


}

void Painter::translate(double tx,double ty)
{
    cairo_translate(cr,tx,ty);
    return;

}
void Painter::translate(const Point& point)
{
    cairo_translate(cr,point.x,point.y);
    return;
	
}
void Painter::translate(const PointF& point)
{
    cairo_translate(cr,point.x,point.y);
    return;
}

void Painter::scale(double sx,double sy)
{
    cairo_scale(cr,sx,sy);
    return;

}

void Painter::scale(const Point& point)
{
    cairo_scale(cr,point.x,point.y);
    return;

}

void Painter::scale(const PointF& point)
{
    cairo_scale(cr,point.x,point.y);
    return;
}



void Painter::saveState()
{

    cairo_save(cr);

}

void Painter::restoreState()
{

    cairo_restore(cr);

}

void Painter::clearRect()
{

    cairo_save(cr);
    cairo_set_operator(cr,CAIRO_OPERATOR_CLEAR);
    cairo_paint(cr);
    cairo_restore(cr);
    return;
}
