#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "Event.h"
#include "Point.h"

enum MouseButtons {
                LeftButton = 1,
                MiddleButton = 2,
                RightButton = 4,
                ScrollUp = 8,
                ScrollDown = 16
};

class MouseEvent : public Event
{
public:
    MouseEvent(Events::Type type,MouseButtons buttons ,Point position);
    ~MouseEvent();
    virtual Events::Type type();
    MouseButtons getButtonState();
    Point getPosition();
private:
    Events::Type m_Type;
    MouseButtons m_ButtonState;
    Point m_Position;

};

#endif // MOUSEEVENT_H
