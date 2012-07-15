#ifndef PAINTER_H
#define PAINTER_H
#include <cairo.h>

class Color;
class Rectangle;
class RectangleF;
class AreaF;
class Surface;
class Widget;
class Point;
class PointF;
class Pattern;
class PaintEvent;

namespace FillRules
{
    enum Rule
    {
        Winding = CAIRO_FILL_RULE_WINDING,
        EvenOdd = CAIRO_FILL_RULE_EVEN_ODD
    };
}

namespace LineCap
{
    enum Type
    {
        Butt    =   CAIRO_LINE_CAP_BUTT,
        Round   =   CAIRO_LINE_CAP_ROUND,
        Square  =   CAIRO_LINE_CAP_SQUARE
    };
}

namespace LineJoin
{
    enum Type
    {
        Miter   =   CAIRO_LINE_JOIN_MITER,
        Round   =   CAIRO_LINE_JOIN_ROUND,
        Bevel   =   CAIRO_LINE_JOIN_BEVEL
    };
}

namespace Operators
{
    enum Type
    {
        Clear   =   CAIRO_OPERATOR_CLEAR,

        Source  =   CAIRO_OPERATOR_SOURCE,
        Over    =   CAIRO_OPERATOR_OVER,
        In      =   CAIRO_OPERATOR_IN,
        Out     =   CAIRO_OPERATOR_OUT,
        Atop    =   CAIRO_OPERATOR_ATOP,

        Destinaton      =   CAIRO_OPERATOR_DEST,
        DestinationOver =   CAIRO_OPERATOR_DEST_OVER,
        DestinationIn   =   CAIRO_OPERATOR_DEST_IN,
        DestinationOut  =   CAIRO_OPERATOR_DEST_OUT,
        DestiantionAtop =   CAIRO_OPERATOR_DEST_ATOP,

        Xor     =   CAIRO_OPERATOR_XOR,
        Add     =   CAIRO_OPERATOR_ADD,

        Saturate    =   CAIRO_OPERATOR_SATURATE
    };
}
class Painter{
	
public:
    Painter(PaintEvent *event);
    Painter(Surface *surface);
    ~Painter();
    void setSource(const Color &color);
    void setSource(const Pattern &pattern);
    void setSource(Surface *, double x, double y);
    void fill();
    void fillPreserve();
    void fillExtents(AreaF& area);
    bool inFill(PointF& point);
    void mask(Pattern& pattern);
    void mask(Surface *surface, double x, double y);
    void paint();
    void paint(double alpha);
    void stroke();
    void strokePreserve();
    void strokeExtents(AreaF &area);
    bool inStroke(PointF& point);
    void pushGroup();
    Pattern* popGroup();
    void popGroupToSource();
    Surface* groupTarget();

    FillRules::Rule fillRule();
    void setFillRule(FillRules::Rule rule);

    LineCap::Type lineCap();
    void setLineCap(LineCap::Type type);

    LineJoin::Type lineJoin();
    void setLineJoin(LineJoin::Type type);

    double lineWidth();
    void setLineWidth(double width);

    double miterLimit();
    void setMiterLimit(double limit);

    Operators::Type operatorType();
    void setOperator(Operators::Type type);

    double tolerance();
    void setTolerance(double tolerance);


    void setClip(Rectangle& clipRectangle);
    void resetClip();
    void copySurface(Surface *,int x, int y);
    void fillRect(double r, double g, double b, double a = 1.0);
    void fillRect(const Color &color);
    void clearRect();
    void translate(double tx,double ty);
    void translate(const Point& point);
    void translate(const PointF& point);
    void scale(double tx,double ty);
    void scale(const Point& point);
    void scale(const PointF& point);
    void setAntialiasing(bool);
    void drawRoundedRect(double x,double y,double width,double height,double radius);
    void saveState();
    void restoreState();

private:
    cairo_t *cr;
    Surface* m_Destination;

};

#endif 
