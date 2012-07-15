#include "Widget.h" 
#include "Application.h"
#include "Painter.h"
#include "Debug.h"
#include "Rectangle.h"
#include "Surface.h"
#include <cairo/cairo-xlib.h>
#include <cstdio>

Widget::Widget(Widget *parentWidget,int x,int y,int width,int height,int flags)
              :m_Origin(x,y),
               m_Size(width,height),
               m_BackgroundColor(0.0,0.0,0.0)
{
	
	
	m_NativeWindowID = 0;
	m_CairoSurface = 0; 
	m_ParentWidget = parentWidget;
	windowSystem->createWidget(this,parentWidget,x,y,width,height);
	
	
}
Widget::~Widget()
{


    std::list<Widget *>::iterator childIter  = m_Children.begin();

    for ( ;childIter != m_Children.end();childIter++)
    {
        delete *childIter;
    }

    if(m_IsTopLevel)
    {
        //if(m_NativeWindowSurface) delete m_NativeWindowSurface;
    }

    if(m_CairoSurface) delete m_CairoSurface;

    if(!m_IsTopLevel)
    {
        m_ParentWidget->m_Children.remove(this);
    }

}


void Widget::getFocus()
{

    windowSystem->grabKeyboardFocus(this);


}

void Widget::toTop()
{
    windowSystem->widgetToTop(this);
}

void Widget::toBottom()
{
    windowSystem->widgetToBottom(this);
}

void Widget::stackAbove(Widget *sibling)
{
    windowSystem->stackAboveWidget(this,sibling);
}

void Widget::stackBelow(Widget *sibling)
{
    windowSystem->stackBelowWidget(this,sibling);
}

void Widget::show()
{
    m_IsVisible = true;
    windowSystem->mapWidget(this);


}

void Widget::hide()
{

    m_IsVisible = false;
    windowSystem->unmapWidget(this);

}

bool Widget::isVisible()
{

    return m_IsVisible;

}

void Widget::update()
{

    Rectangle clipRect(0.0,0.0,width(),height());
    windowSystem->postEvent(this,new UpdateEvent(clipRect));

}

void Widget::update(double x0,double y0,double x1,double y1)
{

    Rectangle clipRect(x0,y0,x1-x0+1,y1-y0+1);
    windowSystem->postEvent(this,new UpdateEvent(clipRect));

    return;
}

void Widget::update(Rectangle clipRect)
{

    windowSystem->postEvent(this,new UpdateEvent(clipRect));

    return;
}

bool Widget::handleEvent(Event *event)
{
    return true;
}

void Widget::resize(Size *size)
{

}
void Widget::resize(int width,int height)
{

}

void Widget::move(Point toPosition)
{
    windowSystem->postEvent(this,new MoveEvent(toPosition));
}

bool Widget::onMouseEvent(MouseEvent *event)
{

        return true;
}


bool Widget::onKeyPressEvent(KeyEvent *event)
{

        return true;
}

bool Widget::onKeyReleaseEvent(KeyEvent *event)
{

        return true;
}
void Widget::onResizeEvent(ResizeEvent *event)
{

}
void Widget::onFocusEvent(FocusEvent *event)
{

}
void Widget::onPaintEvent(PaintEvent* event)
{
	
	debugMessage("Check point :in paintevent\n")
        Painter painter(event);
        painter.fillRect(backgroundColor());
	return;
}


void Widget::setBackground(double r,double g,double b,double a) {
	
        m_BackgroundColor.r = r;
        m_BackgroundColor.g = g;
        m_BackgroundColor.b = b;
        m_BackgroundColor.a = a;
	
	return;
}

void Widget::setBackground(const Color &color) {

	setBackground(color.r,color.g,color.b,color.a);
	
	return;
}


Widget* Widget::childAt(int x,int y) {
        std::list<Widget *>::reverse_iterator childIterator;
        Widget *child = 0;

        for( 	childIterator = m_Children.rbegin();
                        childIterator != m_Children.rend();
                        ++childIterator)
        {
                        child = *childIterator;
                        if(!child->isVisible()) continue;
                        if (child && x >= child->x()  &&  y >= child->y() && x < (child->x() + child->width())  && y < (child->y() + child->height())) return child;
        }

        return 0;
}

