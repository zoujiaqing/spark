#include "WindowSystem.h"
#include "Widget.h"
#include "Point.h"
#include "Debug.h"
#include "Painter.h"
#include "Rectangle.h"
#include "KeyMap.h"
#include "Events.h"
#include "PaintEvent.h"
#include "NativeWindowSurface.h"
#include "PostedEvent.h"
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xrender.h>


WindowSystem::WindowSystem(){}
WindowSystem::~WindowSystem(){}


bool WindowSystem::initialize(){


    m_DefaultDisplay = XOpenDisplay(NULL);
    XRenderPictFormat *format;

    if (m_DefaultDisplay == NULL) {
        return false;
    }
    m_DefaultScreen = DefaultScreen(m_DefaultDisplay);

    XVisualInfo vTemplate;
    XVisualInfo *visualList;
    int visualsMatched;
    vTemplate.c_class = TrueColor;
    vTemplate.depth = 32;
    vTemplate.screen = m_DefaultScreen;
    visualList = XGetVisualInfo (m_DefaultDisplay, VisualDepthMask | VisualClassMask | VisualScreenMask, &vTemplate, &visualsMatched);

    if ( visualsMatched == 0 )
    {
        return false;
    }
    else
    {
        m_DefaultVisual = 0;

        for (int i = 0; i < visualsMatched; i++)
        {
            format = XRenderFindVisualFormat(m_DefaultDisplay, visualList[i].visual);
            if (format->type == PictTypeDirect && format->direct.alphaMask)
            {
                m_DefaultVisual = visualList[i].visual;
                debugMessage("Found argbvisual\n")

                 //return true;
            }
        }
    }

    int eventb, errorb;
    if (XCompositeQueryExtension(m_DefaultDisplay, &eventb, &errorb) == False) {
        debugMessage("composite extension isn't available on server, disabling composite")
                m_UseComposite = false;
        //return false;
    }

    if (XRenderQueryExtension(m_DefaultDisplay, &eventb, &errorb) == False) {
        debugMessage("render extension isn't available on server, disabling composite")
                m_UseComposite = false;
        //return false;
    }
    int minKeycode,maxKeycode;
    KeySym *ksyms;

    XDisplayKeycodes(m_DefaultDisplay, &minKeycode, &maxKeycode);
    ksyms = XGetKeyboardMapping(m_DefaultDisplay,minKeycode,maxKeycode + 1 - minKeycode,&m_MaxKeySymsPerKeyCode);
    m_ModifierMap = XGetModifierMapping(m_DefaultDisplay);

    debug("keycodes per modifier: %d\n",m_ModifierMap->max_keypermod)
            debug("max keysyms per code : %d\n",m_MaxKeySymsPerKeyCode);

    for (int i = 0 ;i<8 ;i++) {
        m_ModifierMasks[i] = 0;
    }

    initModifierMap();
    mouseFocus = 0;
    XFree(visualList);
    XFree(ksyms);
    return true;

}
bool WindowSystem::shutdown(){

        XCloseDisplay(m_DefaultDisplay);
        debugMessage("Deleting toplevel windows \n")
        NativeWindowsMap::iterator toplevelWindowIterator = m_NativeWindows.begin();

        while (toplevelWindowIterator != m_NativeWindows.end()) {
                delete toplevelWindowIterator->second;
                toplevelWindowIterator++;
        }
		//XFree(m_ModifierMap);
		//XFree(m_DefaultDisplay);
		//XFree(m_DefaultVisual);


        return true;
}

void WindowSystem::createWidget(Widget* widget,Widget *parentWidget, int x, int y,int width,int height){

        if (!parentWidget) {

        XSetWindowAttributes attrs;
        attrs.background_pixel = 0x0;
        attrs.override_redirect = 0;
        attrs.border_pixel = 0;

        Colormap colmap =  XCreateColormap(m_DefaultDisplay,RootWindow(m_DefaultDisplay, m_DefaultScreen), m_DefaultVisual, AllocNone);
        attrs.colormap = colmap;
        Window window = XCreateWindow(m_DefaultDisplay,
                                                        RootWindow(m_DefaultDisplay, m_DefaultScreen),
                                                        x,
                                                        y,
                                                        width,
                                                        height,
                                                        0,
                                                        32,
                                                        InputOutput,
                                                        m_DefaultVisual,
                                                        CWBackPixel | CWColormap | CWOverrideRedirect |CWBorderPixel,
                                                        &attrs
                                                        );
        XSelectInput(m_DefaultDisplay, window, ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask |KeyReleaseMask);
        int actualX ,actualY;
        unsigned int actualW ,actualH,b,d;
        Window root;
        XGetGeometry(m_DefaultDisplay,window,&root,&actualX,&actualY,&actualW,&actualH,&b,&d);

        widget->m_NativeWindowID = window;
        widget->m_Origin.x = actualX;
        widget->m_Origin.y = actualY;
        widget->m_Size.width =  actualW;
        widget->m_Size.height = actualH;
        widget->m_IsNative = true;
        widget->m_IsTopLevel =  true;
        widget->m_IsVisible =  true;
        m_NativeWindows.insert(std::make_pair(window,widget));

        if (m_UseComposite) {
                XCompositeRedirectSubwindows(m_DefaultDisplay, window, CompositeRedirectAutomatic);
        }

        widget->m_NativeWindowSurface = new NativeWindowSurface(m_DefaultDisplay,window,m_DefaultVisual,actualW,actualH);
        widget->m_CairoSurface = new Surface(cairo_surface_create_similar(widget->m_NativeWindowSurface->getCairoSurface(),CAIRO_CONTENT_COLOR_ALPHA,actualW,actualH));
        delete widget->m_NativeWindowSurface;

        return;
        }
        widget->m_Origin.x = x;
        widget->m_Origin.y = y;
        widget->m_Size.width =  width;
        widget->m_Size.height = height;
        widget->m_IsNative = false;
        widget->m_IsTopLevel =  false;
        widget->m_IsVisible =  true;
        widget->m_CairoSurface = 0;



        parentWidget->m_Children.push_back(widget);
}


void WindowSystem::destroyWidget(Widget* widget){}

void WindowSystem::moveWidget(Widget* widget, Point toPos)
{
    if(widget->m_IsNative)
    {
        return;
    }
    /*Rectangle *clipRect;
    if (fromPos < toPos)
    {
        clipRect = new Rectangle(fromPos.x,fromPos.y,(toPos.x - fromPos.x) + 1 + widget->width() ,(toPos.y - fromPos.y) + 1 +widget->height());
    }
    else
    {
        clipRect = new Rectangle(toPos.x,toPos.y,(fromPos.x -toPos.x)  + 1 + widget->width() ,(fromPos.y -toPos.y) + 1 +widget->height());
    }*/
    Point fromPos = widget->origin();
    Rectangle rect1(fromPos.x,fromPos.y,widget->width(),widget->height());
    Rectangle rect2(toPos.x,toPos.y,widget->width(),widget->height());

    Rectangle clipRect = unionRect(rect1,rect2);

    widget->m_Origin.x = toPos.x;
    widget->m_Origin.y = toPos.y;


    updateWidget(widget->m_ParentWidget,clipRect);
    


}

Rectangle WindowSystem::unionRect(Rectangle& rect1,Rectangle& rect2)
{
    int r1x0, r1x1, r1y0, r1y1;
    int r2x0, r2x1, r2y0, r2y1;

    int x,y, width ,height;

    r1x0  = rect1.x;
    r1y0  = rect1.y;
    r1x1 =  rect1.x + rect1.width;
    r1y1 =  rect1.y + rect1.height;

    r2x0  = rect2.x;
    r2y0  = rect2.y;
    r2x1 =  rect2.x + rect2.width;
    r2y1 =  rect2.y + rect2.height;

    x = std::min(r1x0,r2x0);
    y = std::min(r1y0,r2y0);
    width  = std::max(r1x1,r2x1) - x;
    height = std::max(r1y1,r2y1) - y;

    return Rectangle(x,y,width,height);


}
void WindowSystem::resizeWidget(Widget* ,int width,int height){}

void WindowSystem::mapWidget(Widget * widget){

        if (widget->m_IsNative) {
                XMapWindow(m_DefaultDisplay, widget->m_NativeWindowID);
        }

        updateWidget(widget);

}
void WindowSystem::unmapWidget(Widget *widget){

        if (widget->m_IsNative) {
                XUnmapWindow(m_DefaultDisplay, widget->m_NativeWindowID);
        }

        updateWidget(widget);


}

void WindowSystem::widgetToTop(Widget *widget)
{
    if(!widget->m_IsTopLevel)
    {
        widget->m_ParentWidget->m_Children.remove(widget);
        widget->m_ParentWidget->m_Children.push_back(widget);
        updateWidget(widget);
    }
}
void WindowSystem::widgetToBottom(Widget *widget)
{
    if(!widget->m_IsTopLevel)
    {
        widget->m_ParentWidget->m_Children.remove(widget);
        widget->m_ParentWidget->m_Children.push_front(widget);
        updateWidget(widget);
    }
}

void WindowSystem::stackAboveWidget(Widget * widget,Widget *sibling)
{
    if(!widget->m_IsTopLevel)
    {
        Widget* parent = widget->m_ParentWidget;
        std::list<Widget *>::iterator widgetPos;
        widgetPos = std::find(parent->m_Children.begin(),parent->m_Children.end(),sibling);
        if (widgetPos == parent->m_Children.end()) return;
        parent->m_Children.remove(widget);
        widgetPos++;
        parent->m_Children.insert(widgetPos,widget);
        updateWidget(widget);

    }
}
void WindowSystem::stackBelowWidget(Widget *widget,Widget *sibling)
{
    if(!widget->m_IsTopLevel)
    {
        Widget* parent = widget->m_ParentWidget;
        std::list<Widget *>::iterator widgetPos;
        widgetPos = std::find(parent->m_Children.begin(),parent->m_Children.end(),sibling);
        if (widgetPos == parent->m_Children.end()) return;
        parent->m_Children.remove(widget);
        widgetPos--;
        parent->m_Children.insert(widgetPos,widget);
        updateWidget(widget);

    }
}
Widget *WindowSystem::widgetAt(int x,int y){}

void WindowSystem::startEventLoop(){


    NativeWindowsMap::iterator toplevelWindowIter;
    Widget *toplevelWindow = 0;
    MouseEvent *mouseevent = 0;
    MouseEvent *mouseevent2 = 0;

    while (1) {
        processPostedEvents();
        XNextEvent(m_DefaultDisplay, &m_Event);

        if ( !toplevelWindow || toplevelWindow->m_NativeWindowID != m_Event.xany.window)
        {

            toplevelWindowIter = m_NativeWindows.find(m_Event.xany.window);
            if (toplevelWindowIter == m_NativeWindows.end()) break;
            toplevelWindow = toplevelWindowIter->second;
        }

        switch(m_Event.type)
        {
            case Expose:
            {
                Surface* cairoSurface = toplevelWindow->m_CairoSurface;
                toplevelWindow->m_NativeWindowSurface = new NativeWindowSurface(m_DefaultDisplay,toplevelWindow->m_NativeWindowID,m_DefaultVisual,toplevelWindow->width(),toplevelWindow->height());

                Painter xPainter(toplevelWindow->m_NativeWindowSurface);
                xPainter.setAntialiasing(false);
                Rectangle rect(m_Event.xexpose.x,m_Event.xexpose.y,m_Event.xexpose.width,m_Event.xexpose.height);
                xPainter.setClip(rect);
                xPainter.copySurface(cairoSurface,0,0);
                xPainter.resetClip();

                XEvent nextEvent;

                while ( XEventsQueued(m_DefaultDisplay,QueuedAfterFlush) )
                {
                    XPeekEvent(m_DefaultDisplay,&nextEvent);

                    if(nextEvent.xany.window == m_Event.xany.window && nextEvent.type == Expose )
                    {

                        XNextEvent(m_DefaultDisplay, &m_Event);
                        Rectangle rect2(m_Event.xexpose.x,m_Event.xexpose.y,m_Event.xexpose.width,m_Event.xexpose.height);
                        xPainter.setClip(rect2);
                        xPainter.copySurface(cairoSurface,0,0);
                        xPainter.resetClip();

                    }
                    else
                    {
                        break;

                    }

                }
                
                delete toplevelWindow->m_NativeWindowSurface;
                break;

            }

            case MotionNotify:
            case ButtonRelease:
            case ButtonPress:
            {
                int _x , _y;
                _x = m_Event.xbutton.x;
                _y = m_Event.xbutton.y;

                Widget * child = toplevelWindow;
                Widget * widget = toplevelWindow;

                while (child = widget->childAt(_x,_y) ){
                    _x = _x - child->x();
                    _y = _y - child->y();
                    widget = child;
                }

                debugMessage("in button ev3\n")

                MouseButtons button;
                switch(m_Event.xbutton.button)
                {
                    case Button1:
                        button = LeftButton;
                        break;
                    case Button2:
                        button = MiddleButton;
                        break;
                    case Button3:
                        button = RightButton;
                        break;
                    case Button4:
                        button = ScrollUp;
                        break;
                    case Button5:
                        button = ScrollDown;
                        break;
                }


                switch (m_Event.type)
                {

                    case ButtonPress:
                        if(mouseevent) { delete mouseevent; mouseevent = 0; }
                        mouseevent = new MouseEvent(Events::MousePress,button,Point(_x,_y));
                        break;
                    case ButtonRelease:
                        if(mouseevent) { delete mouseevent; mouseevent = 0; }
                        mouseevent = new MouseEvent(Events::MouseRelease,button,Point(_x,_y));;
                        break;
                    case MotionNotify:
                    {
                        if (mouseFocus != widget)
                        {
                            if(mouseevent) { delete mouseevent; mouseevent = 0; }
                            mouseevent2 = new MouseEvent(Events::MouseLeave,button,Point(0,0));
                            mouseevent = new MouseEvent(Events::MouseEnter,button,Point(_x,_y));
                            if (mouseFocus) mouseFocus->onMouseEvent(mouseevent2);
                            if(mouseevent2){ delete mouseevent2; mouseevent2 = 0; }

                            mouseFocus = widget;
                        }
                        else
                        {
                            mouseevent = new MouseEvent(Events::MouseMove,button,Point(_x,_y));
                        }
                        break;
                    }
                }

                while(!widget->onMouseEvent(mouseevent) )
                {
                    widget = widget->m_ParentWidget;
                    if(!widget) break;
                }
                break;

            }
        case KeyPress:
            {
                KeyEvent *keyEvent;
                keyEvent = translateXKeyEvent(&m_Event.xkey);

                if(m_KeyboardFocus)
                {

                    m_KeyboardFocus->onKeyPressEvent(keyEvent);

                }
                else
                {
                    toplevelWindow->onKeyPressEvent(keyEvent);
                }

                delete keyEvent;
                break;
            }
        case KeyRelease:
            {
                KeyEvent *keyEvent;
                keyEvent = translateXKeyEvent(&m_Event.xkey);
                if(m_KeyboardFocus)
                {

                    m_KeyboardFocus->onKeyReleaseEvent(keyEvent);
                }
                else
                {
                    toplevelWindow->onKeyReleaseEvent(keyEvent);
                }
                delete keyEvent;
                break;
            }

        }
	
    }


}

void WindowSystem::updateWidget(Widget * widget) {

        Rectangle clipRect(0.0,0.0,widget->width(),widget->height());
        updateWidget(widget,clipRect);


}
void WindowSystem::updateWidget(Widget * widget,Rectangle clipRectangle)
{
    debugMessage("inside update\n")

    Widget * toplevelWidget;
    toplevelWidget = getToplevelParent(widget);

    Painter painter(toplevelWidget->m_CairoSurface);
    Point origin;

    getOriginRelativeToAncestor(widget,toplevelWidget,origin);


    Rectangle newClipRectangle(clipRectangle.x + origin.x,clipRectangle.y + origin.y,
                               clipRectangle.width,clipRectangle.height);

    Rectangle redrawRectangle(origin.x,origin.y,widget->width(),widget->height());

    PaintEvent event(&newClipRectangle,&redrawRectangle,toplevelWidget->m_CairoSurface);


    
    painter.setClip(newClipRectangle);
    painter.setClip(redrawRectangle);
    painter.clearRect();


    debugMessage("calling composeRedraw\n")
    composeRedraw(toplevelWidget,widget,&event);
    Surface *cairoSurface = toplevelWidget->m_CairoSurface;
    toplevelWidget->m_NativeWindowSurface = new NativeWindowSurface(m_DefaultDisplay,toplevelWidget->m_NativeWindowID,m_DefaultVisual,toplevelWidget->width(),toplevelWidget->height());
	
    Painter xPainter(toplevelWidget->m_NativeWindowSurface);
    xPainter.setAntialiasing(false);
    xPainter.setClip(newClipRectangle);
    painter.setClip(redrawRectangle);
    xPainter.copySurface(cairoSurface,0,0);
    
    delete toplevelWidget->m_NativeWindowSurface;

    debugMessage("leaving udate\n")

}

void WindowSystem::composeOn(Widget* widget){
     /*   //TODO: assumes all children are visible and mapped.Should modify to handle other cases

        {
                Painter painter(widget);
                widget->paint(painter);

        }

        if (widget->m_Children.empty()) return;
        std::list<Widget *>::iterator childIterator ;
        for ( childIterator = widget->m_Children.begin();childIterator != widget->m_Children.end();++childIterator) {
                        Widget *child = *childIterator;
                        composeOn(child);
        }
      */

}

void WindowSystem::composeRedraw(Widget* widget,Widget* redrawWidget,PaintEvent *event)
{
        debugMessage("inside composeREdraw\n")
        //TODO: assumes all children are visible and mapped.Should modify to handle other cases
        //PaintEvent paintevent(redrawWidget,clipRect,);

        Point origin;
        getOriginRelativeToAncestor(widget,getToplevelParent(widget),origin);


        Rectangle widgetRect(origin.x,origin.y,widget->width(),widget->height());
        Rectangle pRect;
        Widget* parent = widget->m_ParentWidget;

        if(!widget->m_IsTopLevel)
        {
            getOriginRelativeToAncestor(parent,getToplevelParent(parent),origin);
            pRect.x = origin.x;
            pRect.y = origin.y;
            pRect.width = parent->width();
            pRect.height = parent->height();
        }

        event->init(widget,&widgetRect,&pRect);
        widget->onPaintEvent(event);

        Widget *child;
        if (widget->m_Children.empty()) return;
        std::list<Widget *>::iterator childIterator ;


        for ( childIterator = widget->m_Children.begin();childIterator != widget->m_Children.end();++childIterator) {
                        child = *childIterator;
                        
                        
                        if (child->isVisible() && areOverlapping(child,redrawWidget))	{
                                debugMessage("found overlap\n")
                                composeRedraw(child,redrawWidget,event);
                        }
                        
        }


}

bool WindowSystem::areOverlapping(Widget *widget1 , Widget *widget2) {
        int w1_t,w1_l,w1_r,w1_b;
        int w2_t,w2_l,w2_r,w2_b;

        Widget *commonParent;

        if((commonParent = getToplevelParent(widget1)) != getToplevelParent(widget2)) return false;
        Point trueOrigin1;
        Point trueOrigin2;
        getOriginRelativeToAncestor(widget1,commonParent,trueOrigin1);

        w1_l = trueOrigin1.x;
        w1_t = trueOrigin1.y;
        w1_r = trueOrigin1.x + widget1->width() - 1;
        w1_b = trueOrigin1.y + widget1->height() - 1;

        getOriginRelativeToAncestor(widget2,commonParent,trueOrigin2);

        w2_l = trueOrigin2.x;
        w2_t = trueOrigin2.y;
        w2_r = trueOrigin2.x + widget2->width() - 1;
        w2_b = trueOrigin2.y + widget2->height() - 1;
        //taken from: 	http://www.siliconchisel.com/articles/fast-window-overlap-checking-algorithm/
        return ( (((w1_t - w2_b) ^ (w1_b - w2_t)) & ((w1_l - w2_r) - (w1_r - w2_l))) < 0 ? true : false) ;
}

Widget* WindowSystem::getToplevelParent(Widget *widget) {
        Widget *tl_parent;
        if (tl_parent = widget->m_ParentWidget) {;
                while (tl_parent->m_ParentWidget) {
                 tl_parent = tl_parent->m_ParentWidget;
                };
        } else {
                return widget;
        }


        return tl_parent;
}

void WindowSystem::getOriginRelativeToAncestor(Widget *widget, Widget* relativeToWidget,Point &point) {

        int x , y;

        x = widget->x();
        y = widget->y();
        Widget* widget1 = widget;
        if (widget1->m_ParentWidget) {
        while(widget1->m_ParentWidget != relativeToWidget) {
                x += widget1->m_ParentWidget->x();
                y += widget1->m_ParentWidget->y();
                widget1 = widget1->m_ParentWidget;
        }
    }
        point.x = x;
        point.y = y;


}

void WindowSystem::grabKeyboardFocus(Widget *widget){

    FocusEvent focusGain(Events::FocusGain);
    FocusEvent focusLost(Events::FocusLoss);
    if (widget) {

    if (m_KeyboardFocus == widget) return;
    if (m_KeyboardFocus) m_KeyboardFocus->onFocusEvent(&focusLost);
    m_KeyboardFocus = widget;
    widget->onFocusEvent(&focusGain);

    }
}

void WindowSystem::initModifierMap() {

    int i =0 ,j= 0,k = 0;
    KeyCode *modifiers;
    modifiers = m_ModifierMap->modifiermap;
    int keyspermod = m_ModifierMap->max_keypermod;
    int maxsyms = m_MaxKeySymsPerKeyCode;

    KeySym keysym;


    for (i = 0 ; i< 8 ;++i) {
        for (j = 0 ; j < keyspermod;++j )   {
            for (k = 0 ; k < 4;++k)       {

                keysym = XKeycodeToKeysym(m_DefaultDisplay, modifiers[(i * keyspermod) + j],k);

                if (keysym == XK_Shift_L || keysym == XK_Shift_R)  m_ModifierMasks[i] = Shift;
                if (keysym == XK_Control_L  || keysym == XK_Control_R ) m_ModifierMasks[i] = Control;
                if (keysym == XK_Alt_L  || keysym == XK_Alt_R ) m_ModifierMasks[i] = Alt;
                if (keysym == XK_Caps_Lock) m_ModifierMasks[i] = CapsLock;
                if (keysym == XK_Num_Lock ) m_ModifierMasks[i] = NumLock;
                if (keysym == XK_Meta_L  || keysym == XK_Meta_R ) m_ModifierMasks[i] = Alt;
                if (keysym == XK_Super_L  || keysym == XK_Super_R ) m_ModifierMasks[i] = Super;
            }
        }
    }


}

KeyEvent* WindowSystem::translateXKeyEvent(XKeyEvent *event)
{

    char *buffer = new char[20];
    KeySym keysym;
    int modifiers;

    XLookupString(event,buffer,20,&keysym,0);
    Keys::Key key = translateKeySymtoKey(keysym);
    Events::Type type = (event->type == KeyPress) ? Events::KeyPressed : Events::KeyReleased;
    modifiers = translateStateToKeyboardModifiers(event->state);
    KeyEvent *keyEvent = new KeyEvent(type,key,buffer,modifiers,false);

    return keyEvent;

}

int WindowSystem::translateStateToKeyboardModifiers(int state)
{
    int modifiers = 0;
    if (state & ShiftMask)      modifiers |= m_ModifierMasks[0];
    if (state & LockMask)       modifiers |= m_ModifierMasks[1];
    if (state & ControlMask)    modifiers |= m_ModifierMasks[2];
    if (state & Mod1Mask)       modifiers |= m_ModifierMasks[3];
    if (state & Mod2Mask)       modifiers |= m_ModifierMasks[4];
    if (state & Mod3Mask)       modifiers |= m_ModifierMasks[5];
    if (state & Mod4Mask)       modifiers |= m_ModifierMasks[6];
    if (state & Mod5Mask)       modifiers |= m_ModifierMasks[7];
    return modifiers;
}

void WindowSystem::postEvent(Widget *receiver,Event *event)
{
    if(receiver && event)
    {
        PostedEvent* postedEvent = new PostedEvent(receiver,event);
        m_PostedEventsQ.push(postedEvent);

    }
    return;
}

void WindowSystem::processPostedEvents()
{
    PostedEvent* postedEvent = 0;
    Widget *receiver = 0;
    Event *event = 0;
    Events::Type eventType;
    while(!m_PostedEventsQ.empty()) {
        postedEvent = m_PostedEventsQ.front();
        m_PostedEventsQ.pop();
        eventType = postedEvent->m_Event->type();
        event = postedEvent->m_Event;
        receiver = postedEvent->m_Receiver;

        switch(eventType)
        {
            case Events::Update:
                //updateWidget(receiver,((UpdateEvent *)event)->getUpdateRectangle());
                updateWidget(receiver);
                break;
            case Events::Move:
                moveWidget(receiver,((MoveEvent *)event)->m_ToPos);
                break;
        }

        delete postedEvent;
        delete event;

    }
}
