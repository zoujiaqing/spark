#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H
#include "Event.h"
#include "Rectangle.h"
class UpdateEvent : public Event
{
public:
    UpdateEvent(Rectangle updateRectangle);
    Events::Type type();
    Rectangle getUpdateRectangle();
private:
    Rectangle m_UpdateRectangle;
};

#endif // UPDATEEVENT_H
