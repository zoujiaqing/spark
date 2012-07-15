#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include "Widget.h"
#include "Color.h"

class TestWidget : public Widget
{

    public:

    TestWidget(Widget *parentWidget,int x,int y,int width,int height);
    virtual void onPaintEvent(PaintEvent *event);
    virtual bool onMouseEvent(MouseEvent *event);
    virtual bool onKeyPressEvent(KeyEvent *event);
    virtual bool onKeyReleaseEvent(KeyEvent *event);
    spark::signal<int(void)> clicked;

    private:

     Color m_DownColor;
     int state;
     Color m_EnterColor;
     char *m_Text;
     Widget *childWidget;
     bool mousepressed;
     Point startp;


};

#endif // TESTWIDGET_H
