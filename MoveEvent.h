#ifndef MOVEEVENT_H
#define MOVEEVENT_H
#include "Event.h"
#include "Point.h"
class MoveEvent : public Event
{
public:
    MoveEvent(Point toPos);
    Events::Type type();
    Point m_ToPos;
};

#endif // MOVEEVENT_H
