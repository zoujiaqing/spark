#ifndef WINDOW_SYSTEM_H
#define WINDOW_SYSTEM_H 1

#include <X11/Xlib.h>
#include <cairo/cairo.h>
#include <map>
#include <queue>
#include <algorithm>

#include "KeyMap.h"

class Painter;
class Widget;
class Point;
class Rectangle;
class PaintEvent;
struct PostedEvent;

typedef Window NativeWindow;
typedef unsigned int WidgetID; 
typedef std::map<NativeWindow,Widget *> NativeWindowsMap;
typedef std::queue<PostedEvent *> PostedEventsQueue;

class WindowSystem
{

public:
    WindowSystem();
    ~WindowSystem();

    bool initialize();
    bool shutdown();

    void startEventLoop();

    void createWidget(Widget* widget,Widget *parentWidget, int x, int y,int width,int height);
    void destroyWidget(Widget* widget);

    void moveWidget(Widget* widget,Point toPos);
    void resizeWidget(Widget* ,int width,int height);

    void mapWidget(Widget *);
    void unmapWidget(Widget *);

    void widgetToTop(Widget *);
    void widgetToBottom(Widget *);
    void stackAboveWidget(Widget *,Widget *);
    void stackBelowWidget(Widget *,Widget *);
    void updateWidget(Widget *);
    void updateWidget(Widget *,Rectangle clipRectangle);

    void grabKeyboardFocus(Widget *);

    bool areOverlapping(Widget *widget1 ,Widget *widget2);

    Widget* widgetAt(int x,int y);
    Widget* getToplevelParent(Widget *widget);
    void getOriginRelativeToAncestor(Widget*,Widget*,Point&);
    
    void postEvent(Widget *receiver,Event *event);



private:
    friend class Widget;
    Display *m_DefaultDisplay;
    int m_DefaultScreen;
    Visual *m_DefaultVisual;
    XEvent m_Event;    
    NativeWindowsMap m_NativeWindows;
    PostedEventsQueue m_PostedEventsQ;
    int m_MaxKeySymsPerKeyCode;
    XModifierKeymap *m_ModifierMap;
    int m_ModifierMasks[8];
    Widget *mouseFocus;
    Widget *m_KeyboardFocus;
    bool m_UseComposite;

    void initModifierMap();
    void composeOn(Widget* widget);
    void composeRedraw(Widget* widget,Widget *redrawWidget,PaintEvent* event);
    Rectangle unionRect(Rectangle& rect1,Rectangle& rect2);
    KeyEvent * translateXKeyEvent(XKeyEvent *event);
    int translateStateToKeyboardModifiers(int state);
    void processPostedEvents();


};



#endif 
